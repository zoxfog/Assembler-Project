#include "converter.h"

/*****************************************************************************************************************/
/* this file includes function that convert types,number presentation(octal and decimal) and binary presentations*/
/******************************************************************************************************************/




/* this functions converts binary string to an octal number*/
/* returns an octal number presented in int*/

int binary_to_octal(char * bin)
{
    int oct = 0, dec = 0, i = 0;

    /* converting binary to decimal*/
    while (i <= MILA )
    {

         dec += (bin[i]-'0') * pow(2, (MILA-i)); 
         ++i;
    }
    
    i=1;
  
    /* converting decimal to octal*/
    while (dec != 0 )   
    {
        oct += (dec % 8) * i;
        dec /= 8;
        i *= 10;
     }
     return oct;
}


/* this function converts a decimal int to a binary string*/
/* arguments are the given decimal and the number of bits of the output string*/
/* returns a string the represents the bit number*/

char *decimal_to_binary(int n,int bits)
{
   int c, d, count;
   char *pointer;
   
   count = 0;
   pointer = (char*)malloc(bits+1);
   
   if (pointer == NULL)
   {
      printf("cannot allocate memory");
      exit(0);
   }

   /* for every bit insert 1 or 0*/    
   for (c = (bits-1) ; c >= 0 ; c--)
   {
      d = n >> c;
     
      if (d & 1)
         *(pointer+count) = 1 + '0';
      else
         *(pointer+count) = 0 + '0';
     
      count++;
   }

   *(pointer+count) = '\0';
   
   return  pointer;
}


/* this function converts a binary number to its two complement's equivalent*/
/* arguments are the binary number string and the number of bits*/
/* returns a binary number string with the given bit length in two complement*/

char * twos_complement(char *code, int bits)
{
    char  onesComp[bits + 1];
    char twosComp[bits + 1];
    int i, carry=1;



    /* Find ones complement of the binary number */
    for(i=0; i<bits; i++)
    {
        if(code[i] == '1')
        {
            onesComp[i] = '0';
        }
        else if(code[i] == '0')
        {
            onesComp[i] = '1';
        }
    }
    onesComp[bits] = '\0';


     /* Add 1 to the ones complement  for the two complement*/
    for(i=bits-1; i>=0; i--)
    {
        if(onesComp[i] == '1' && carry == 1)
        {
            twosComp[i] = '0';
        }
        else if(onesComp[i] == '0' && carry == 1)
        {
            twosComp[i] = '1';
            carry = 0;
        }
        else
        {
            twosComp[i] = onesComp[i];
        }
    }
    twosComp[bits] = '\0';

 

    char *b;
    b = (char*)malloc(bits+1);
    strcpy(b,twosComp);


    return b;
}



/* this function coverts an number into a given size string*/
/*arguments are size of the string and the number */ 
/* returns the string that includes the given int
if string size is bigger than the int's size
the number 0 will be inserted in the rest of the elements*/
     
char * num_tostring(int size, long number)
{

     long temp1;
     int temp2;
     temp1 = number;

     int divider = 10;      
     char str_temp[size+1];

     memset(str_temp,'\0',size+1);
  
     /* for every digit in the number insert it into a string elemnt*/   
     int i;
     for (i=(size-1); i>=0 ; i--)
     {
          /* divide it by 10,find it's remainder and insert it*/
          temp2 = (temp1 % divider);
          str_temp[i]=temp2 + '0';
          temp1 = temp1/divider;
     }
     
     char *str;
     str=malloc(sizeof(str_temp));
     strcpy(str,str_temp);
  
     return str;
}
   
        
/* this function writes the binary code onto the "mila"*/
/* arguments are A,R,E field, the int number to be coded, start posiiton and end poisition*/
/* returns a string of binary numbers representing the mila*/

char *coder( ARE are, int num, int start, int limit)
{ 

     int k;
     char *temp2;
     char temp[MILA+2] = "000000000000000";
     temp2 = (char*)malloc(MILA+2);
   
     char *subcode;/* sub code for the num to be converted into*/
     k = limit-start;
    
     /* write the sub code, write it in two's complement if negative*/
     if (num<0)
          subcode = twos_complement(decimal_to_binary ( abs(num) , k), k);
     else
          subcode = decimal_to_binary ( num , k);
 
    /* write the A R E field*/
    temp[MILA-(int)are] = '1';  

    /* insert the sub code into the "mila"*/
    for (k = (MILA-limit+1); k <= (MILA-start) ; k++)
          temp[k] = subcode[k-(MILA-limit+1)];

    strcpy(temp2,temp);
						
     return temp2;
}



     
