
/******************************************************************************************/
/*this file includes the verification functions, for every input from the source file,
 the functions return it's type. for example if it is a number, label call, register etc.*/
/****************************************************************************************/


#include "assembler.h"



#define MING 9 /* define guidance type length*/
#define MINC 5 /* define opcode  length*/

/* this function verifies whether the given input is an opcode*/
/* argument is a pointer to the input from a given line*/
/* returns the opcode number +1 if opcode is valid else 0*/

int opcode_v(char *pointer)
{  

    /* for any opcode commads with 3 characters such as mov, add, rts etc.*/

    char sub[MINC];
    memset(sub, '\0', sizeof(sub));


   int k;

    char *opcode_s[]={"NIL","mov","cmp","add","sub","lea","clr","not","inc","dec","jmp","bne","red","prn","jsr","rts","stop"};
    int length = 3;
    int opcode_i;
  

    /* the following lines scan whether the given pointer/string is equal 
     to one of the opcode commands*/ 
    if (strlen(pointer)>=length)  
    { 

      strncpy(sub,pointer, length);
	
         for (k=1; k<OPCODES; k++)
          {
                if (!strcmp(opcode_s[k],sub))
                {
                      opcode_i=k;

                      return opcode_i;
                }
           }
     }
 
     memset(sub, '\0', sizeof(sub));    

      /*length of stop*/    
    length = 4;    
     
     /* for the command "stop" only*/   
     if (strlen(pointer)>=length) 
     {    
          memcpy(sub, pointer, length);     
          if (!strcmp(opcode_s[k],sub))
                {
                      opcode_i=k;

                      return opcode_i;
                }
     }


     return 0;
}


/* this function checks if the given line is blank*/
/* argument is a pointer to the start of a new line*/
/*returns 1 if blank else 0*/

int blankline_v(char *pointer)
{
    int k;

    /* if first character is not a new line*/
    if (*pointer!='\n')
    {
        /*if the line is black*/
        for(k=0; k<strlen(pointer); k++)
        {
              if (pointer[k]!=' ' && pointer[k]!='\t')
              return 0;
        }

    }
       
    return 1;
}



/* this function verifies if the given input is a label*/
/* argument is a pointer to the input from a given line*/
/* returns the label's length if it is a label, else 0*/
 

int label_v(char *pointer)
{
    /*length counter*/
    int cnt = 0;
    /* temporary pointer*/
    char *temp;
   /* max label size*/
    int labelsize=31;

    /* scan the input*/
    for ( temp=pointer;temp<(pointer+strlen(pointer));temp++)
    {
  
         if (isalpha((int)*temp) || (isdigit((int)*temp) && cnt>0 && cnt <= labelsize))
               cnt++;
   
         else if (cnt>0 && (*temp==':' || *temp==' ' || *temp=='\t' || *temp=='\n' || *temp==','))
                return cnt;

         else break;
     }

     return 0;
}

/* this function verifies if the given input is a guidance*/
/* argument is a pointer to the input from a given line*/
/* returns the number of guidance as written in the maman book if true, else 0*/ 
int guidance_v( char *pointer)
{
     char sub[MING]; 
     memset(sub, '\0', sizeof(sub));  
    
     int length=strlen(".data");
     
     /* if line is long enough check if it is "data"*/
     if ( length <= strlen(pointer))  
    { 
          strncpy(sub, pointer, length); 
          if (!strcmp(".data",sub))
                   return data;

     }

     length = strlen(".entry");
     if (strlen(pointer)>=length)  
    { 
          strncpy(sub, pointer, length);   
          if (!strcmp(".entry",sub))
                  return entry;
     }

     length =strlen(".string");
     if (strlen(pointer)>=length)  
    { 
          strncpy(sub, pointer, length);   
          if (!strcmp(".string",sub))
                  return string;

          /*check if it is "extern"*/
          strncpy(sub, pointer, length);   
          if (!strcmp(".extern",sub))
                  return externn;

     }
     return 0;
}

/* this function verifies if the given input is a number*/ 
/* argument is a pointer to the input from a given line*/
/*if it is a number it returns the number. 
if it is not a number or it is not a valid input return 0.5.
we wish to return 0.5 and not 0 because 0 is a valid number*/
   
double number_v (char *pointer)
{ 
   int k=0;
   int number;
   double  false_num = 0.5;



   /* check if starts with -,+ or a digit*/
   if ( !isdigit((int)pointer[k]) && pointer[k]!='-' && pointer[k]!='+')
         return false_num;

   /* counts number of digits*/
   k++;
   while (isdigit((int)pointer[k]) )
        k++;

   /* if the end of the number end with a valid character*/
   if (pointer[k]!=' ' && pointer[k]!='\t' && pointer[k]!=',' && pointer[k]!='\n') /*|| (k==1 && !isdigit((int)pointer[k])))*/
        return false_num;
      
   /* scan the sumber from a string*/
   char sub[k+1];
   memset(sub, '\n', k+1);


   strncpy(sub, pointer, k);
   number = atoi(sub);
 
   return (double)number;
} 


      

