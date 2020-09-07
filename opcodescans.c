 #include "assembler.h"

#define DIVIDER 10
   

/* this function scans an opcode command input 
and adds the it's code to the code table*/
/*arguments are table array, line position pointer, 
source flag, target flag and opcode operand counter*/ 
/*retruns the length of the opcode if no error occureced else ERROR*/

int opcode_scan (table_p *table, char *linep,fp source,fp target,int *op_cnt)
{
    /* retrieve the type of opcode*/
    commands c= opcode_v(linep);

    int length;    
    if (c==stop)
        length = strlen("stop");
    else length = strlen("mov");

    /*validity check*/
    if(source->OPCODE==ON)
    {
          printf("\nLine %d: invalid opcode call.\n",ln);
          return ERROR;
     }

    /*create a row for the code table and write it's code*/
     add2table(&table[CODE_TABLE], coder(A,(int)c-1,OPCODEP,MILA+1), IC++); 

    /* if it is a label line,point   at the code table*/
    if(source->LABELLINE==OFF)
         table[SYMBOL_TABLE]->code_node = table[CODE_TABLE];
    
    /* change flags for validation of successive inputs*/
    int temp = 0;
    opcode_f(source, target, c,&temp);
    *op_cnt = temp;

    return length;
}


/* this function scans for a hash number
and then creates the code and inserts it in the code table*/
/* arguments are table array line position pointer,  source flag and target flag*/
/*retruns the length if no error occurred else ERROR*/
   
int scan_hash(table_p *table,char * linep,  fp source,fp target)
{

     int length=0;
 
     /* if there is a + or - sign update length*/   
     if(*(linep+1)=='+' || *(linep+1)=='-')
         length++;
    
     /*validation check*/
     if( source->INSTANT==ON && target->INSTANT==ON)
     {
           printf("\nLine %d: invalid '#' call.\n", ln);
           return ERROR;
      }

    /*get the number and verify it*/
     double false_num= 0.5; /*0.5 for the number verification function*/
     double num = number_v(1+linep);

     /* if number is not valid*/
     if (num==false_num)
      {
          printf("\nLine %d: '#' is not followed by a number.\n",ln);
          return ERROR;
      }

      /* comma validity check*/
      if (source->COMMA ==OFF)
      {
            printf("\nLine %d: missing comma sign before '#'.\n" , ln);
            return ERROR; 
      }
 
        /*create a row for the data table and write it's code*/
        add2table(&table[CODE_TABLE],coder( A, (int)num ,TARGETP ,MILA+1), IC++);
   
        /* if is a source operand*/
      if (source->INSTANT==OFF)
      {
           /* update the opcode command code*/
           (table[CODE_TABLE]->next)->symbolORcode[MILA-SOURCEP]='1';

          /* change flags for succesive inputs*/
           flags_on(&source);
           source->COMMA=OFF;
      }

      /* validate flags for successive inputs for target */ 
      else if(target->INSTANT==OFF)
     {
           if(target->NOSOURCE==OFF)
                    (table[CODE_TABLE]->next)->symbolORcode[MILA-TARGETP]='1';
 
           else
                   ((table[CODE_TABLE]->next)->next)->symbolORcode[MILA-TARGETP]='1';

          flags_on(&target);
     }
 
    /*count the size of the input to update the length*/  
    int n = abs((int)num); 
    while (n != 0) 
    {
        n /= DIVIDER;    
        length++;
    }

     return length;
}

/* this function scans a register pointer input and writes the mila code accordingly*/
/*arguments are table array line position pointer, source flag and target flag*/
/*retruns the length of the input if no error occurred else ERROR*/

int scan_registerp(table_p *table, char *linep, fp source,fp target)
{ 

     /* define register limits*/
     int regmax = 7;
     int regmin =0;

     int operand_index;/* for the string index in the mila code*/
     
     int length =3; /*define register char length*/

     int k;
     
     /*create a string for the register input*/
     char sub[length+1];  
     memset(sub, '\0',length+1);
     strncpy(sub, linep, length);
 
    
     /* validation test*/
     if (source->INDIRECT_R==ON && target->INDIRECT_R==ON)
      {
            printf("\nLine %d: invalid register call '%s'.\n", ln,sub);
            return ERROR;
      }
      
      /* check if register number exists*/     
      if (sub[2]<regmin && sub[2]>regmax)
      {
            printf("\nLine %d: the given register '%s' does not exist.\n", ln, sub);
            return ERROR;
       }
       
       /*comma validation check for target input*/           
       if (target->INDIRECT_R==OFF && source->COMMA==OFF)
       {     
             printf("\nLine %d: missing comma before '%s'.\n", ln , sub);
             return ERROR;
       }
       
      /* find the matching register number from 0-7 to code the right mila*/
      for( k=regmin; k<=regmax && k!=atoi(&sub[2]) ; k++){}

      operand_index = 5;
      
      /* for a source register input */
      if(source->INDIRECT_R==OFF)
      {
           /*add to the codes table and code it to mila*/ 
           add2table(&table[CODE_TABLE],coder( A, k ,SOURCEP-1 ,SOURCEP+2), IC++);
           (table[CODE_TABLE]->next)->symbolORcode[operand_index]='1';
                                             
           /*flag change for successive inputs*/ 
           flags_on(&source);
           source->COMMA=OFF;
      }

      /* for target addressing*/ 
      else if(target->INDIRECT_R==OFF)
      {
           /* if both source and target are register addressing*/ 
           if((table[CODE_TABLE]->next)->symbolORcode[operand_index]=='1' || (table[CODE_TABLE]->next)->symbolORcode[operand_index-1]=='1' )
           {
                /* update the opcode command code*/
               operand_index = 9;
               (table[CODE_TABLE]->next)->symbolORcode[operand_index]='1';
               char *temp = coder( A, k ,TARGETP ,SOURCEP-1);

               int i;
               for (i=0; i<=MILA; i++)
               {
                    if (temp[i]=='1')
                       table[CODE_TABLE]->symbolORcode[i]='1';
               }
 
           }

           /*if only target is a register*/
           else
           {
                   /* write the code and add it to the data table*/
                   operand_index = 9;
                   add2table(&table[CODE_TABLE],coder( A, k ,TARGETP ,SOURCEP-1), IC++);

                   if(target->NOSOURCE==OFF)
                         (table[CODE_TABLE]->next)->symbolORcode[operand_index]='1';
           
                   else
                        ((table[CODE_TABLE]->next)->next)->symbolORcode[operand_index]='1';

            }

           flags_on(&target);
       }

       return --length;
}
               
/* this function scans a register input and writes the mila code accordingly*/
/*arguments are line position pointer, source flag and target flag*/
/*retruns OFF if no error occured else ON*/

int scan_register(table_p *table, char *linep, fp source,fp target)
{ 

     /* define register limits*/
     int regmax = 7;
     int regmin =0;

     int operand_index;
     
     /*define register char length*/
     int length =2;

     int k;

     /*create a string for the register input*/
     char sub[length+1];  
     memset(sub, '\0',length+1);
     strncpy(sub, linep, length);

     /* validation test*/
     if (source->DIRECT_R==ON && target->DIRECT_R==ON)
      {
            printf("\nLine %d: invalid register call '%s'.\n", ln,sub);
            return ERROR;
      }
      
      /* check if register number exists*/     
      if (sub[1]<regmin && sub[1]>regmax)
      {
            printf("\nLine %d: the given register '%s' does not exist.\n", ln, sub);
            return ERROR;
       }

    
       /*comma validation check for target input*/           
       if (target->DIRECT_R==OFF && source->COMMA==OFF)
       {     
             printf("\nLine %d: missing comma before '%s'.\n", ln , sub);
             return ERROR;
       }
     
      /* find the matching register number from 0-7 to code the right mila*/
      for( k=regmin; k<=regmax && k!=atoi(&sub[1]) ; k++){}
   
      operand_index = 4;
      /* for a source register input */
      if(source->DIRECT_R==OFF)
      {
           /*add to the codes table and code it to mila*/ 

           add2table(&table[CODE_TABLE],coder( A, k ,SOURCEP-1 ,SOURCEP+2), IC++);
           (table[CODE_TABLE]->next)->symbolORcode[operand_index]='1';
                        
                     
           /*flag change for successive inputs*/ 
           flags_on(&source);
           source->COMMA=OFF;
      }

      /* for target addressing*/ 
      else if(target->DIRECT_R==OFF   )
      {

 
           /* if both source and target are register addressing*/ 
           if((table[CODE_TABLE]->next)->symbolORcode[operand_index]=='1' || (table[CODE_TABLE]->next)->symbolORcode[operand_index+1]=='1' )
           {
               operand_index = 8;
               (table[CODE_TABLE]->next)->symbolORcode[operand_index]='1';

               char *temp = coder( A, k ,TARGETP ,SOURCEP-1);

               int i;

               for (i=0; i<=MILA; i++)
               {
                    if (temp[i]=='1')
                       table[CODE_TABLE]->symbolORcode[i]='1';
               }
           }

           /*if only target is a register*/
           else
           {
                   operand_index = 8;
                   add2table(&table[CODE_TABLE],coder( A, k ,TARGETP ,SOURCEP-1), IC++);

                   if (target->NOSOURCE==OFF)
                         (table[CODE_TABLE]->next)->symbolORcode[operand_index]='1';
           
                   else
                        ((table[CODE_TABLE]->next)->next)->symbolORcode[operand_index]='1';

            }

           flags_on(&target);
       }

       return --length;
}                    
   
