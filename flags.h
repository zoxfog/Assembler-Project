#ifndef FLAGS_H
#define FLAGS_H

#include <stdio.h>
#include <stdlib.h>

#define ON 1
#define OFF 0
#endif


typedef struct flags * fp; /* flags pointer*/

typedef struct flags {
            unsigned int CODE: 1;
            unsigned int LABEL: 1;
            unsigned int LABELLINE: 1; /* if the first input of the line is a label declaration*/
            unsigned int COMMA: 1;
            unsigned int NOSOURCE: 1;/* if the source file is irrelevent, like "inc"*/


            
            /* for guidance lines*/
            unsigned int GUIDANCE: 1;
            unsigned int ENTRY: 1;
            unsigned int EXTERN: 1;
            unsigned int DATA: 1;
            unsigned int NUMBER: 1;
            unsigned int STRING: 1;
            unsigned int CHAR: 1;

            /* for opcode command lines*/
            unsigned int OPCODE: 1;
            unsigned int INSTANT: 1;
            unsigned int DIRECT: 1;
            unsigned int INDIRECT_R: 1;
            unsigned int DIRECT_R: 1;

               }flag ;

typedef enum {mov=1,cmp,add ,sub , lea, clr, nott, inc, dec, jmp, bne, red, prn, jsr, rts, stop} commands; 






/* flag functions*/
void opcode_f(fp ,fp , commands,int*);
void flags_on (fp*);



