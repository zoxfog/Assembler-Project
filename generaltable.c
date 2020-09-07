
/******************************************************************/
/* this file includes operational functions for the general tables*/
/******************************************************************/


#include "generaltable.h"



/*this function adds a label/symbol to the table*/
/*arguments are the table (data, symbol, code .etc)
, a symbol name or code and an IC/DC address*/

void add2table ( table_p * head, char *l,int ad)
{
     table_p   t;
     
     t=(table_p)malloc(sizeof(node1));

     char *sORc;/* symbol or code*/
     sORc= (char*)malloc(strlen(l)+1); 
     strcpy(sORc,l);
     
     if (!t || !sORc)
     {
          printf("cannot allocate memory");
          exit (0);
      }
      
      t->symbolORcode = sORc;
      t-> address= ad;  
      t->ext = OFF;
      t->ent = OFF;
      t->code_node = NULL;


      if(!(*head))
      {
           t->next = NULL;
           *head = t;
           return;
       }
 
       t->next = *head;
       *head = t;
       return;

}

/* this function frees  the table's and list's memory*/
/* arguments are the given table*/

void freeall (table_p *head)
{            
      table_p q;


      while (*head)
      {
          q=*head;
          *head = q->next ;
          free(q);
      }
}

/* this function searches for a symbol 
and returns a pointer to the symbol, if symbol does not exist return NULL
if the symbol exists more than once return NULL and NULLify the name*/
/*areguments are the given table and a symbol name*/

table_p search(table_p * head, char *n)
{
     table_p temp1,temp2;

     temp1=*head;


      if (!(*head))
          return NULL;

      while ((temp1)!=0)
      {

           
           if(!strcmp(temp1->symbolORcode,n))
           {

                temp2=(table_p)malloc(sizeof(temp1));
                temp2=temp1;

                return temp2;
           }

           temp1=temp1->next;
      }
        
      
      return NULL;
}
          
   

