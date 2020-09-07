# Assembler-Project

## Description
This project is represents an assembler. Given 20 different commands that are ment to be processed by a comupter, this program translates the commands to machine language so that the computer can distinguish between the intended actions.
Each command is translated into binary code and stored in a different memory set. In this projects the memory sets are 7 Registers and a RAM (stack).

Each command is also reflected by its own attrubutes:
- The memory sets in which it is restricted to, for example a command may be stored only in register number 1, 2 and RAM.
- Addressing methods, 3 addressing methods are used: Absolute, Relocatable and External. Thus a command may have 1 to 3 addressing methods.
- Syntanx and command sequence, some commands may or may not apear after\after a certain character or other command.

To address the various restrictions each command may present I created the flags file. 
flags acts a unique data structure which is consists of different flags in order to avoid errors.



