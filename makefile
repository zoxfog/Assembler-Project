
myprog1 : main.o firstscan.o secondscan.o labelscan.o opcodescans.o guidancescans.o converter.o filewriter.o flags.o generaltable.o verifications.o
	gcc -g main.o firstscan.o secondscan.o labelscan.o opcodescans.o guidancescans.o converter.o filewriter.o flags.o generaltable.o verifications.o -ansi -Wall -pedantic -lm -o myprog1 -lm
main.o : main.c assembler.h
	gcc -c main.c -ansi -Wall -pedantic -o main.o -lm

firstscan.o : firstscan.c assembler.h
	gcc -c firstscan.c -ansi -Wall -pedantic -o firstscan.o -lm

secondscan.o : firstscan.c assembler.h
	gcc -c secondscan.c -ansi -Wall -pedantic -o secondscan.o -lm

labelscan.o : labelscan.c assembler.h
	gcc -c labelscan.c -ansi -Wall -pedantic -o labelscan.o -lm

opcodescans.o : opcodescans.c assembler.h
	gcc -c opcodescans.c -ansi -Wall -pedantic -o opcodescans.o -lm

guidancescans.o : guidancescans.c assembler.h 
	gcc -c guidancescans.c -ansi -Wall -pedantic -o guidancescans.o -lm

converter.o : converter.c converter.h
	gcc -c converter.c -ansi -Wall -pedantic -o converter.o -lm

filewriter.o : filewriter.c assembler.h
	gcc -c filewriter.c -ansi -Wall -pedantic -o filewriter.o -lm

flags.o  : flags.c flags.h
	gcc -c flags.c -ansi -Wall -pedantic -o flags.o -lm


generaltable.o : generaltable.c generaltable.h
	gcc -c generaltable.c -ansi -Wall -pedantic -o generaltable.o -lm

verifications.o : verifications.c assembler.h
	gcc -c verifications.c -ansi -Wall -pedantic -o verifications.o -lm




