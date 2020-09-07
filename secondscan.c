
/****************************************/
/* this file represents the second scan*/
/***************************************/

/*this function is the second scan, it writes the mila binary code
for entry and extern symbols and  updates the tables */
/*argument are the tables array, and the file name*/
/* returns ERROR if an error occured, else 0*/

#include "assembler.h"

int second_scan(table_p *t, char *file)
{

      table_p temp1 ;
      table_p temp2 = t[SYMBOL_OPERAND_TABLE];
      table_p temp3;

        /* scan the operand symbol list*/
      while (temp2) 
      {

            temp1=search(&t[SYMBOL_TABLE],temp2->symbolORcode);
            temp3=search(&t[SYMBOL_GUIDANCE_TABLE],temp2->symbolORcode);
 
 									
            /*code for non external symbol operands*/
           if (temp1!=NULL)
           {
 
                 /*update symbol-operand- table's ent flag if it is an entry symbol*/
                 if (temp3!=NULL && temp3->ent==ON)
                 {
                           temp2->address = temp1->address;
                           temp2->ent=ON;
                 }
                 
                 (temp2->code_node)->symbolORcode = coder( R, temp1->address,TARGETP,  MILA+1);
           }
           
             							
           /* code for external symbols and update symbol-operand-tabl'es ext flag */
           if (temp3!=NULL  && temp3->ext==ON)
           {
                 temp2->ext=ON;            
                 (temp2->code_node)->symbolORcode =coder( R, 1, 0, MILA+1);                 
           }

           /* if there's a symbol operand in listhead2 not defined as entry or extern*/
           if (temp1==NULL && temp3==NULL)
              {
                    printf("\n%s is undefined, symbol has no source.\n-------------------> in file: %s.as\n",temp2->symbolORcode, file); 
                    return ERROR;  
              }       

       temp2=temp2->next;
      }
      
       /* for every entry symbol in symbol-guidance-table, rewrite it's address from symbol table*/      
       temp3 = t[SYMBOL_GUIDANCE_TABLE];
       while (temp3)
       {
            
            temp1 = search(&t[SYMBOL_TABLE],temp3->symbolORcode);
            if (temp3->ent==ON)
            {
                     if( temp1 )
                            temp3->address = temp1->address;
                     else
                     { 
                         printf("\nThe entry symbol %s is not defined, cannot assign IC memory.\n",temp3->symbolORcode);
                         return ERROR;
                     }
            }

      temp3 = temp3->next;
      }

      return 0;
}





