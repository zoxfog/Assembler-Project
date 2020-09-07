
#ifndef CONVERTER_H
#define CONVERTER_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MILA 14 /* mila: binary byte index size*/

typedef enum {A=2,R=1,E=0} ARE;

int binary_to_octal(char *);

char *decimal_to_binary(int ,int );

char * twos_complement(char *code, int bits);

char * num_tostring(int size, long number);

char *coder( ARE are, int num, int start, int limit);

#endif
