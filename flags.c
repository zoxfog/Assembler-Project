
/*************************************************/
/* this file includes the function for the flags*/
/*************************************************/



#include "flags.h"



/* this function restarts all flags to ON mode*/
/* argument is a given flag struct*/

void flags_on (fp *flagp)
{
    free(*flagp);
    fp ptr;
    ptr = (fp)malloc( sizeof(flag));
        if (!ptr)
        {
            printf("cannot allocate memory");
            exit(0);
        }
    
    ptr->CODE = ON;
    ptr->LABEL=ON;
    ptr->LABELLINE=ON;
    ptr->COMMA=ON;
    ptr->NOSOURCE=ON;

    ptr->GUIDANCE=ON;
    ptr->ENTRY=ON;
    ptr->EXTERN=ON;
    ptr->DATA=ON;
    ptr->NUMBER=ON;
    ptr->STRING=ON;
    ptr->CHAR=ON;

    ptr->OPCODE=ON;
    ptr->INSTANT=ON;
    ptr->DIRECT=ON;
    ptr->INDIRECT_R=ON;
    ptr->DIRECT_R=ON;
    *flagp=ptr;
    return;
}



/* this function resets all flags to the right opcode mode and changes to opcode counter */
/* arguments are source flag, target flag, the opcode command and a pointer to the op counter*/

void opcode_f(fp source,fp destination, commands command ,int *opcnt)
{ 
    /* reset flags first*/
    flags_on(&source);
    flags_on(&destination);

    switch(command)
    {
   
         case mov:
         case add:
         case sub:

              source->INSTANT=OFF;
              source->DIRECT=OFF;
              source->INDIRECT_R=OFF;
              source->DIRECT_R=OFF;
         
              destination->DIRECT=OFF;
              destination->INDIRECT_R=OFF;
              destination->DIRECT_R=OFF;

              *opcnt=2;
              
              break;

        case cmp: 

              source->INSTANT=OFF;
              source->DIRECT=OFF;
              source->INDIRECT_R=OFF;
              source->DIRECT_R=OFF;

  
              destination->INSTANT=OFF;       
              destination->DIRECT=OFF;
              destination->INDIRECT_R=OFF;
              destination->DIRECT_R=OFF;

              *opcnt=2;

              break;

        case lea:

              source->DIRECT=OFF;
  
              destination->DIRECT=OFF;       
              destination->INDIRECT_R=OFF;
              destination->DIRECT_R=OFF;

              *opcnt=2;

              break;
       
        case clr:
        case nott:
        case inc:
        case dec:
        case red:

              destination->NOSOURCE=OFF;
      
              destination->DIRECT=OFF;
              destination->INDIRECT_R=OFF;
              destination->DIRECT_R=OFF;

              *opcnt=1;

              break;
       
        case jmp:
        case bne:
        case jsr:

              destination->NOSOURCE=OFF;
      
              destination->DIRECT=OFF;
              destination->INDIRECT_R=OFF;

              *opcnt=1;
             break;
        case prn:

              destination->NOSOURCE=OFF;

              destination->INSTANT=OFF;       
              destination->DIRECT=OFF;
              destination->INDIRECT_R=OFF;
              destination->DIRECT_R=OFF;

              *opcnt=1;

              break;
  
        default:

              *opcnt=0;

              break;
    }

}  
              
              
              
       
              
                














    
    
