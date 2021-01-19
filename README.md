# Assembler-Project

## Description
This project is a representation of an assembler. Given list 16 different commands that are ment to be processed by a comupter, this program translates the commands to machine language so that the computer can distinguish between the intended actions.
Each command is translated into machine language (binary code) and stored in a different memory set. In this projects the memory sets are 7 Registers and a RAM (stack).

Each command is also reflected by its own attrubutes:
- The memory sets in which they are restricted to, for example a command may be stored only in register number 1, 2 and RAM.
- Addressing methods, 3 addressing methods are used: Absolute, Relocatable and External. Thus a command may have 1 to 3 addressing methods.
- Syntanx and command sequence, some commands may or may not apear after\after a certain character or other command.

To address the various restrictions each command may present I therefore created the flags file. 
'flags' act as a unique data structure which consists of different warning flags in order to avoid errors.



Run example:<br/>
############################################<br/>
############################################<br/>
LOOP: prn #48<br/>
LABEL1:     .entry <br/>
LABEL2<br/>
LABE*L3: inc 
laaaaaaaaaaaaaaaaaaaaaaaa<br/>
 mov #56,#56<br/>
 sub r1, r4 , r3, K<br/>
mov r1r2<br/>
mov r1 r2<br/>
 cmp  #-6<br/>
     bne END<br/>
     dec K<br/>
     jmp LOOP<br/>
END: stop<br/>
STR: .string "abcd"<br/>
STR: .string "abcd"<br/>
LIST: .data 6, -9<br/>
 .data -100<br/>
 .data "artt"<br/>
 .string 5<br/>
 .data<br/>
K: .data 31<br/>
############################################<br/>
############################################<br/>

<img src="https://raw.githubusercontent.com/zoxfog/Assembler-Project/master/run%20example/test3.png" width="850" height="600">


*This is a university class project.
