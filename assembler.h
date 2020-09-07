#include "flags.h"
#include "generaltable.h"
#include "converter.h"


#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <ctype.h> 
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ON 1
#define OFF 0
#define ERROR -1


#define MAXSIZE 100
#define MEMORY 100
#define MAXL 82 /* max length of each line */
#define OPCODES 16


#define MILA 14 /* mila: binary byte index size*/
#define OPCODEP 11 /*index position of the opcode  code in the mila*/
#define TARGETP 3 /* index poisition of the target code in the mila*/ 
#define SOURCEP 7 /* index poisition of the source code in the mila*/ 


extern int IC;
extern int DC;

extern int ln;



typedef enum {data=1, string, entry, externn} guidances;
typedef enum { SYMBOL_TABLE, SYMBOL_OPERAND_TABLE, SYMBOL_GUIDANCE_TABLE,DATA_TABLE, CODE_TABLE} talbe_t;


/*verification functions*/
int opcode_v(char *);
int blankline_v(char *);
int label_v(char *);
int guidance_v( char *);
double number_v (char *);


/* first scan/second scan functions*/
int first_scan(table_p *,char *);
int second_scan(table_p *, char *);
int get_type(char *);


/* filewriter functions*/
void file_writer(table_p *,int,char *);

/* label scan functions*/
int label_scan(table_p *,char *, fp, fp);

/* opcode functions*/
int opcode_scan (table_p *,char *, fp, fp,int*);
int scan_hash(table_p *,char * ,fp ,fp );
int scan_registerp(table_p *,char *, fp,fp);
int scan_register(table_p *,char *, fp,fp );

/* guidance functions*/
int number_scan(table_p *,char *, fp, fp);
int scan_guidance(table_p *,char *,fp );
int scan_string(table_p *,char *linep,fp );


#endif
















