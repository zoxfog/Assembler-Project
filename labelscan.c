


/*******************************************************/
/* this file includes the label/symbol scanner function*/
/*******************************************************/


#include "assembler.h"

#define DIVIDER 10


/* this function scans a label, adds it to the symbol table (for defined symbols),
 or adds it to the operand symbol tabe*/
/*arguments are the tables array, line poisition pointer,source flag and target flag*/
/* returns the length of the symbol if an no error occured else ERROR*/

int label_scan(table_p *table, char *linep, fp source, fp target )
{  
     int length;/* for the label name length*/
     int maxsize = 31;/* max length of a label*/

     /* get label length*/
     length=label_v(linep);

     
     char name[length+1];
     memset(name, '\0', sizeof(char)*(length+1));

     /* get label name*/
     strncpy(name, linep, length);

     /* if exceeds the length of 31 chars*/
     if (length>maxsize)
     {
         printf("\nLine %d: '%s' label call is too long.\n", ln,name);
         return ERROR;
     }
        
     /* if the label is an operand*/
     if (source->DIRECT==OFF || target ->DIRECT==OFF)
     {

          /*make sure comma flag is off*/
          if (source-> COMMA==OFF)
          {
             printf("\nline %d: missing comma before '%s'.\n", ln ,name);
             return ERROR;
          }
     
          int operand_index= 6;/*the string index in the mila code*/

          /* update the opcode command code for the target/spurce operand*/
          if( source->DIRECT==OFF)
                  table[CODE_TABLE]->symbolORcode[operand_index]='1';
          else if (target->NOSOURCE==OFF)
                  table[CODE_TABLE]->symbolORcode[operand_index+4]='1';/* +4 for the target operand position*/
          else
                  (table[CODE_TABLE]->next)->symbolORcode[operand_index+4]='1';/* +4 for the target operand position*/

          /*create a row(node) in the code table without a code, to be added in the future*/    
          add2table(&table[CODE_TABLE],coder(R ,0, 0, MILA+1), IC++);
 
          /* check if the symbol has been defined*/
          table_p match = search(&table[SYMBOL_TABLE], name);

          /* update length*/
          length--;

          if(match==NULL)
          {

                /* add to the operand symbol table if the symbol has not yet been defined
                 and point it at the code table node*/
                add2table(&table[SYMBOL_OPERAND_TABLE],name, MEMORY + IC + DC-1);               
                table[SYMBOL_OPERAND_TABLE]->code_node = table[CODE_TABLE];               

                /* change flags*/
                if( source->DIRECT==OFF)
                {                     
                       source->DIRECT=ON;
                       source->COMMA=OFF;
                 }
                 else target->DIRECT=ON;
                
          }
          
          /* if the symbol has been defined code it to the code table*/
          else
          {
               table[CODE_TABLE]->symbolORcode = coder(R ,match->address, TARGETP, MILA+1); 
                
               /* change flags for succesive validation*/         
               if( source->DIRECT==OFF)
               {
                    source->DIRECT=ON;
                    source->COMMA=OFF;
               }
               else target->DIRECT=ON;
          }

     }



     /* validation check if the label being defined ends with a ':'*/                        
     else if(*(linep+length)!=':')
     {
           
           printf("\nLine %d: label definition call '%s' is missing ':'.\n", ln,name);
           return ERROR;
     }
     
     else
     {
            /* another validation check*/
           if (source->LABEL==ON)
           {
               printf("\nLine %d: '%s' is an invalid label call.\n", ln,name);
               return ERROR;
           }
          
           
           /* check if this label definition is followed by an entry/extern call, to be ignored*/
           int temp=length+1;
           while ((*(linep+temp) =='\t' || *(linep+temp)==' ' ) && (linep+temp)<(linep + strlen(linep)))
                 temp++;

             /* if not followed by an entry/external guidance call*/
            if (guidance_v(linep+temp)!=entry && guidance_v(linep+temp)!=externn)
           {


                  /*check if the label is already defined*/
                 if (search(&table[SYMBOL_TABLE], name))
                 {

                        printf("\nLine %d: the label declaration '%s' failed, '%s' is already defined.\n" , ln, name,name);
                        return ERROR;
                  }
           
                 /* add to the symbol table*/
                 add2table(&table[SYMBOL_TABLE], name,MEMORY + IC + DC);
             
                 /* adjust flags for successive validation*/
                 flags_on(&source);
                 source-> DATA = OFF;
                 source->STRING =OFF;
                 source-> OPCODE = OFF;
                 source->LABELLINE=OFF;
           }

           else
           {
                flags_on(&source);
                source->EXTERN=OFF;
                source ->ENTRY=OFF;
            }

      }



      return length;
}
