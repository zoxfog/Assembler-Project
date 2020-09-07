
/*****************************************************************************/
/* this file includes the file writer function that writes the output files*/
/*****************************************************************************/

#include "assembler.h"


#define ADDRESS 5 /*address code length*/
#define OCODE  4 /*octal code length*/
#define OCTAL 8  /* octal base number*/





/* this function writes the object, entry and external files if no prior errors occurred*/
/* arguments are the tables struct array, error flag and the originals file's name*/
 
void file_writer(table_p *table,int error_val, char *file)
{

       char *ending[3] = {".ob",".ext",".ent"};

      /* don't write files if error flag in on*/
      if(error_val<=ERROR)
           return;


      table_p temphead; /* used for the head of a given table*/

      int k;
      int i;
      int oct;

      char *num_str; 

      /*stacks for the the decimal memorys and the octal codes, respectively. to be printed later*/
      char *stack1[1][MEMORY+IC+DC+2];
      char *stack2[1][MEMORY+IC+DC+2];

      char filename[MAXSIZE];

      FILE *fptr;

      typedef enum {OBJECT,EXTERNAL ,ENTRY} file_type;
    
      /* for every file type*/
      file_type t; 
      for (k=0; k<3  ; k++)
        {
                /* check if an external symbol exists, if not continue*/
                temphead = table[SYMBOL_GUIDANCE_TABLE];
                while(temphead && temphead->ext==OFF)
                        temphead=temphead->next;
               if (!temphead && k==EXTERNAL)
                        continue;

                /* check if an entry symbol exists, if not continue*/
                temphead = table[SYMBOL_GUIDANCE_TABLE];
                while(temphead && temphead->ent==OFF)
                        temphead=temphead->next;
                if (!temphead && k==ENTRY)
                       continue;
                
   

               /* create the new file names, cut the name of the source file and add .ob,.ent or .ext*/
              memset(filename,'\n', MAXSIZE);
              strcpy(filename, file);
        
              fptr = fopen(strcat(filename, ending[k]), "w");
              if (fptr == NULL)
              {
                   printf("file error!");
                   exit(0);
              }

              /*for each case output file case*/
              t=k;
              switch (t)
              {
                    case OBJECT:

                         /* insert the data table codes into the stack for every DC*/
                         temphead=table[DATA_TABLE];
                         for (i=(DC-1); i>=0; i--)
                         {
                               stack1[0][i+IC]=num_tostring(OCODE,i+MEMORY+IC);
                               oct = binary_to_octal(temphead->symbolORcode);
                               stack2[0][i+IC] = num_tostring(ADDRESS, oct);

                               temphead=temphead->next;
                         }

                         /* insert the code table codes into the stack for every IC*/
                         temphead=table[CODE_TABLE];
                         for (i=(IC-1); i>=0; i--)
                         {     
                               stack1[0][i]=num_tostring(OCODE,i+MEMORY);
                               oct = binary_to_octal(temphead->symbolORcode);
                               stack2[0][i] = num_tostring(ADDRESS, oct);

                               temphead=temphead->next;
                         }

                         /*print IC and DC at the top of the output file*/
                         fprintf(fptr,"   %d       %d\n", IC, DC);

                         /* print out the stacks on output file*/
                         for (i=0; i<(IC+DC); i++)
                         {
                               fprintf(fptr," %s     %s\n", stack1[0][i], stack2[0][i]);

                               free(stack1[0][i]);
                               free(stack2[0][i]);
                         }

                         break;

                   case ENTRY:

                         /* print the entry symbols from the symbol guidance table*/
                         temphead = table[SYMBOL_GUIDANCE_TABLE];
                         while(temphead)
                         {                     
                               if(temphead->ent==ON)
                               {
                                    num_str = num_tostring(OCODE, temphead->address);
                                    fprintf(fptr,"%s    %s\n", temphead->symbolORcode, num_str);
                                    free(num_str);
                               }

                               temphead=temphead->next;
                        }

                        break;
   
                  case EXTERNAL:

                         /* print the external symbols from the symbol operand table*/                
                         temphead = table[SYMBOL_OPERAND_TABLE];
                         while(temphead)
                         {
                     
                               if(temphead->ext==ON)
                               {
                                    num_str = num_tostring(OCODE, temphead->address);
                                    fprintf(fptr,"%s    %s\n", temphead->symbolORcode, num_str);
                                    free(num_str);
                               }

                               temphead=temphead->next;
                         }

                        break;
                  
                  default: break;

            }/*end of switch*/
             
            fclose(fptr);
     
       }/* end of for loop*/ 
  
}/* end of function*/                         
   
                          
     
