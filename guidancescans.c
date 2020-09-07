#include "assembler.h"
#define DIVIDER 10


/* this function scans a number input for data and  then creates the code and inserts it in the data table*/
/*arguments are the abble array, line position pointer, source flag and target flag*/ 
/*returns the length of the total input */

int number_scan(table_p *table ,char *linep,fp source,fp target)
{

    /* get the given integer input*/
    int n = (int)number_v(linep);

   
    /*validity check*/
    if (source->NUMBER==ON)
    {
         printf("\nLine %d: '%d' is an invalid number call.\n",ln,n);
         return ERROR;
    }

    /* for data inputs*/
    if( source->NUMBER==OFF)
    {    
         /*if numbers aren't separated with a comma*/
         if( source->COMMA==OFF)
         {
              printf("\nLine %d: missing comma before %d.\n", ln ,n);
              return ERROR; 
         }

         else 
         {   

             /*create a row for the data table and write it's code*/
             add2table(&table[DATA_TABLE],coder( E, n ,0,MILA+1), DC++); 

             /* if it is a label line,point the symbol listhead 
             to the data table*/
             if(source->LABELLINE==OFF)
                table[SYMBOL_TABLE]->code_node=table[DATA_TABLE];

              
         /* change flags for validation of successive inputs*/
         source->LABELLINE=ON;
         source->COMMA=OFF;
         }

     }

     /* update the length*/
     int length = 0;
     if ((*linep)=='+' || (*linep)=='-')
          length++;

       while (n != 0) {
        n /= DIVIDER;    
        ++length;
    }

        
   return --length;
}


                  
/* this function scans a guidance input*/
/*arguments are line position pointer, listhead1, listhead3, source flag and target flag*/
/*retruns the length if no error occured else ERROR*/  
                 
int scan_guidance(table_p *table, char *linep,fp source)
{
      int length=0;

      /* get the guidance type*/
      int guidance_type = guidance_v( linep);
    
     /* each case represents a guidance type, numbers according to the maman book
     each case includes a validation check, flag change and line pointer poisiton update*/
     switch(guidance_type)
     {
          case data:
              /*validation check*/ 
              if (source->DATA==ON)
              {
                   printf("\nLine %d: invalid '.data' call\n",ln);
                   return ERROR;
              }
              
              /* if a label was declared reset flags to ON but keep labelline OFF*/
              if(source->LABELLINE==OFF)
              {
                   flags_on(&source);
                   source->LABELLINE=OFF;
              }

              else flags_on(&source);

              source->NUMBER=OFF;
               
              /* update the length*/
              length = strlen("data"); 
              break;
                   
          case string:
              /* validation check*/
              if (source->STRING==ON)
              {
                   printf("\nLine %d: invalid '.string' call\n",ln);
                   return ERROR;
               }
              
              /* if a label was declared reset flags to ON but keep labelline OFF*/
              if(source->LABELLINE==OFF)
              {
                   flags_on(&source);
                   source->LABELLINE=OFF;
              }

              else flags_on(&source);
              source->CHAR=OFF;
            
              /* update length*/
              length = strlen("string"); 
              break;
            
          case entry:
              /* validation check*/
              if(source->ENTRY==ON)
              {
                   printf("\nLine %d: invalid '.entry' call.\n",ln);
                   return ERROR;
              }
          
              flags_on(&source);
              length = strlen("entry")+1;
             
              /* scan for a successive label*/
              while ((*(linep+length) =='\t' || *(linep+length)==' ' ) && (linep+length)<=(linep + strlen(linep)))
                 length++;

              /*if label verified add it to the entry/external(guidance) symbol table*/
              if (label_v(linep+length))
              {

                     char name [label_v(linep+length)+1];
                     memset(name,'\0',label_v(linep+length)+1); 
                     strncpy(name, linep+length, label_v(linep+length));
                 
                     /* update length*/
                     length+= label_v(linep+length)-1;
                 
                    /* if the symbol has'nt been defined as an entry/ external yet*/
                    if (search (&table[SYMBOL_GUIDANCE_TABLE],name)==NULL)
                    {
                         /* add it the the symbol guidance table*/
                         length += label_v(linep+length);
                         add2table(&table[SYMBOL_GUIDANCE_TABLE],name,MEMORY + IC + DC);
                         table[SYMBOL_GUIDANCE_TABLE]->ent = ON;
                    }     
              }

              /* if there is no label input after the guidance input*/
              else 
              {
                    printf("\nLine %d:invalid entry guidance line, missing a label call.\n" , ln);
                    return ERROR;
              }
  
              /* reset flags*/           
              flags_on(&source);             
              break;

          case externn:
              /* validation check*/
              if(source->EXTERN==ON)
              {
                   printf("\nLine %d: invalid '.entry' call.\n",ln);
                   return ERROR;
              }
              length = strlen("extern")+1;

              /* scan for a successive label*/
              while ((*(linep+length) =='\t' || *(linep+length)==' ' )&& (linep+length)<=(linep + strlen(linep)))
                 length++;
                   
           /*if label verified add it to the entry/external(guidance) symbol table*/
              if (label_v(linep+length))
              {

                     char name [label_v(linep+length)+1];
                     memset(name,'\0',label_v(linep+length)+1); 
                     strncpy(name, linep+length, label_v(linep+length));

                      /* update length*/
                     length+= label_v(linep+length)-1;
              
                    if (search (&table[SYMBOL_GUIDANCE_TABLE],name)==NULL)
                    {
                         /* add it the the symbol guidance table*/
                         length +=label_v(linep+length);
                         add2table(&table[SYMBOL_GUIDANCE_TABLE],name,MEMORY + IC + DC);
                         table[SYMBOL_GUIDANCE_TABLE]->ext=ON;
                    }     
              }   
       
              /* if there is no label input after the guidance input*/
              else 
              {
                    printf("\nLine %d:invalid extern guidance line, missing a label call.\n" , ln);
                    return ERROR;
              }
             
              flags_on(&source);
              break;
      }
      return length;
}

/* this function scans a string input*/
/*arguments are tables array line position pointer and source flag*/
/*retruns the length if no error occured else ERROR*/   

int scan_string(table_p *table, char *linep,fp source)
{
     int length = 1;

   
     /*validity check*/
     if(source->CHAR==ON)
     {
         printf("\nLine %d: invalid string call.\n", ln);
         return ERROR;
     }
  
     char * linep2 = linep;

     /* checking to see if the string ends with " for validation*/
     while (*(linep2+length)!='"' && (linep2+length)<= (linep+strlen(linep)))
     {
         if((linep2+length) ==(linep+strlen(linep)) && *(linep2+length)!='"')
         {
              printf("\nLine %d: string end undefined.\n",ln);
              return ERROR;
         }
         length++;      
     }
     
     length=1;

     /*scan the characters, add it to the data table 
      and code their mila code*/
     while (*(linep+length)!='"' )
     {
       
        /*create a row for the data table and write it's code*/
        add2table(&table[DATA_TABLE],coder( E, (int)(*(linep+length)) ,0,MILA+1), DC++); 

         /* if it is followed by a label/symbol*/
         if(source->LABELLINE==OFF)
         {
                /* point the symbol at the data table's node*/
                table[SYMBOL_TABLE]->code_node=table[DATA_TABLE];
                source->LABELLINE=ON;
         }
     
        length++;
     }

     /* write the code on to the data table*/
     add2table(&table[DATA_TABLE],coder( E, 0 ,0,MILA+1), DC++); 
     
     /*flag change for successive validation*/
      flags_on(&source);
      source->CHAR=OFF;
      
      return length;
}
