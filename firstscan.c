

/**********************************************/
/*this file includes the first scan functions*/
/*********************************************/


#include "assembler.h"



/* this function scans each line and for each input verifies it 
and than calls the right function to write the mila code*/
/* arguments are the tables, and the name of the file*/
/* returns ERROR (-1) if an error occurred else 0*/

int first_scan(table_p *t ,char *file)
{     

    int type;    /* for the type of scanned char*/
    char *p;    /* pointer to the position in the line*/
    int appender; /*appender to file line pointer buffer*/ 
    int op_cnt;  /* operand counter for each operand command*/

    int file_error=OFF;  /*initilaize error flag for the whole file*/

    fp source=NULL;   /*pointer to 'flags structure' for the source operand or the next input*/
    fp target=NULL;  /*pointer to 'flags structure' for the destination operand*/

    /*  restart all falgs, and turn them on */
    flags_on(&source);
    flags_on(&target);

     char filename[MAXSIZE];
     strcpy(filename, file);
 
     /* reset line counter*/
     ln =0;  

    FILE *fptr;
    fptr=fopen(strcat(filename, ".as"),"r");
       if (fptr == NULL)
       {
            printf("file error!");
            exit(0);
        }

     /* scan each line and insert it to *line*/

       char line[MAXSIZE];

    /* scan each line and insert it to *line*/
       while (fgets(line, sizeof(line), fptr)) 
       { 

        /* append line number*/
        ln++;      

        /*check if the line exceeds the limit*/
        if (strlen(line)>=MAXL)
        {
           printf("\nLine %d: line exceeds line limit of 80 characters.\n",ln);
           printf("--------------------> in file %s\n", filename);
           continue;
        }

         /* check if it is a blank line or a comment line*/
        if ((*line)!=';' && !blankline_v(line))
        {   
               /*  restart all falgs, and turn them on */
               flags_on(&source);
               flags_on(&target);

              /* turn off flags for first valid possible inputs*/ 
              source->LABEL = OFF;
              source->ENTRY = OFF;
              source->EXTERN = OFF;
              source->OPCODE = OFF;
              source->DATA = OFF;
              source->STRING = OFF;
              op_cnt=0; 


             /* for every line*/     
             for (p=line; p<(line+strlen(line));p++)
             {
                
                 appender = 0;

                 /*get the input type and calls the scan function accordingly*/	               
                 type=get_type(p);
  
                 switch(type)
                 {

                     /* case comma*/
                     case ',':	
                          /* comma validation*/
                          if ( source->COMMA==ON)
                          {
                              printf("\nLine %d: comma position undefined.\n", ln);
                              printf("--------------------> in file %s\n", filename);     
                              appender++;
                          }
                          else 
                               source->COMMA=ON;

                          break;

                     case '\n':
                     case '\t':
                     case ' ':

                          break;

                    /* operand command case*/                  
                     case 'o':	
                          appender = opcode_scan(t ,p,source,target,&op_cnt);
                          p = p + appender;

                          break;

                  /* label case*/
                     case 'l':
                         appender = label_scan(t ,p,source, target );
                          p = p + appender;

                         /*  if is a label definition*/                 
                         if((*p)!=':') 
                              op_cnt--;


                         break;
                      
                     /* number case*/
                      case 'n':		
                         appender = number_scan(t ,p,source,target);
                          p = p + appender;

                         break; 
             
                     /* register case*/
                      case 'r':	
                         appender = scan_register(t ,p ,source, target);
                          p = p + appender;
                          op_cnt--;

                          break;
                     
                     /*guidance case*/
                     case 'g':
                         appender = scan_guidance(t ,p,source);
                          p = p + appender;											
							                    
                          break;
                        
                     /* indirect register case*/ 
                     case '*':
                         appender = scan_registerp(t ,p ,source, target);
                          p = p + appender;
                          op_cnt--;

                          break;

                     /*hash (instant assignning) case*/
                      case '#':	
                         appender = scan_hash(t ,p, source, target);
                          p = p + appender;
                          op_cnt--;
										
                          break;
            
                     /* string case*/
                     case 's':
                         appender = scan_string(t ,p ,source);
                          p = p + appender;

                          break;

                     default:
                          appender = ERROR;
                          printf("\nLine %d: undefined input at '%c'\n",ln, *p);

                         break; 

              }/*end of switch*/

              /* turn on file error if needed*/
              if (appender == ERROR)
              {   
                  op_cnt=0;  
                  break;
              }


           }/* end of for loop*/

         /* check if operand count is proper*/
          if(op_cnt!=0)
          {
              printf("\nLine %d: %s.\n", ln, ((op_cnt<0)?"too many operands":"not enough operands"));
              appender = ERROR;
          }

         /* if one of the functions returned an ERROR, update the error flag*/
          if (appender ==ERROR)
          {
                file_error=ERROR;
                printf("--------------------> in file %s\n", filename);
          }

       }/* end of if*/


    }/* end of while*/

     fclose(fptr);
		
     return file_error;

}/* end of function*/

                              

/* this function scans a given input catagorizes it
 and returns the right type of input for the switch statement
in the first scan function, uses verification functions*/ 
/* argument is a a pointer to the poisition in the line*/
/* returns the ascii code of the char*/

int get_type(char *pointer)
{

    if (opcode_v(pointer))
          return 'o';

    if (strlen(pointer)>2  && *pointer=='r' && isdigit((int)*(pointer+1)) && 
   (*(pointer+2)==' ' || *(pointer+2)=='\n' || *(pointer+2)=='\t'||*(pointer+2)==',' ))
          return 'r';

    if (strlen(pointer)>3  && *pointer=='*' && *(pointer+1)=='r' && isdigit((int)*(pointer+2)))
          return '*';

    if (label_v(pointer) )
          return 'l';

    if (strlen(pointer)>2  && *pointer=='#')
          return '#';

    if (guidance_v(pointer))
          return 'g';

    if (number_v(pointer)!=0.5)
         return 'n';

    if ( *pointer=='"' && strlen(pointer)>2)
         return 's';

    if (*pointer==' ' || *pointer=='\t' || *pointer==','  ||  *pointer=='\n' )
         return *pointer;

    return 'u';
}



