
/**********************************************************************************/
/* this program is assembler creating a machine language
 by converting different commands to binary and then octal and assigning their memory*/
/*************************************************************************************/




#include "assembler.h"
#define TABLES 5


int ln;
int IC;
int DC;

int main (int argc, char *argv[])
{
    int error;/* -1 for errors*/
    int j;
    int i;
    ln = 0;

    /* initialize the 5 tables*/
    /* symbol table: for defined tables*/
    /* symbol operand table: for operand symbols/labels*/
    /* symbol guidance table: for extern and entry symbols*/
    /* data table for DC data codes*/
    /* code table for IC code codes*/   
    table_p tables[TABLES];
    for(j=0; j<TABLES; j++)
       tables[j]=NULL;
    
    /* for each file */
    for (i=1; i<argc; i++)
    {

        IC=0;
        DC=0;

        /* first scan*/
        error = first_scan(tables,argv[i]);

        /* seconds scan*/   
        error += second_scan(tables, argv[i]);

        /* write the files after gathered all the symbols and codes*/
        file_writer(tables,error,argv[i]);

       for(j=0; j<TABLES; j++)
           freeall(&tables[j]);

    }


 return 0;   
}

