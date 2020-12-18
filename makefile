#Macros?
CC = gcc
CFLAGS = -O -Wall -pedantic -std=c11 -g

#Dependencies
Source : Source.o readFile.o priorityQueue.o printStats.o

Source.o : a2.h readFile.h priorityQueue.h Source.h
readFile.o : readFile.h a2.h
priorityQueue.o : priorityQueue.h a2.h
printStats.o : a2.h


#misc targets
clean:
	rm -f *.o core Source
	
run: Source
	./Source "a2in.txt" 48
