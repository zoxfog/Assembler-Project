#ifndef GENERALTABLE_H
#define GENERALTABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define OFF 0
#define ON 1


typedef struct general_table * table_p; /*symbol list pointer*/

typedef struct general_table {

               char *symbolORcode;   /* label name or mila code*/
               int  address ;   /* memory decimal assignment*/

               int ext;      /* ON for external else OFF*/
               int ent;      /* ON for entry else OFF*/

               table_p code_node; /* pointer to the right position in the code-table/data-table */
               table_p next;

                         } node1;


/*symbol list functions*/
void add2table ( table_p *, char *, int);
void freeall (table_p* );
table_p search(table_p* , char *);

#endif
