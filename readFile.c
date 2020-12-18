#include <stdio.h>
#include <stdlib.h>
#include "readFile.h"
#include "a2.h"
//ORDER:    priority, cpu, io, runTime;


//Function to read in file to processArray
void readFile(char* fileName, int size, process processArray[]){

	FILE* inFile;
	if((inFile = fopen(fileName, "r")) == NULL){
		printf("\nPROBLEM OPENING inFILE in readFile.c\n");		//error check system call
	}
	int arrayCounter = 0;

	while(size > arrayCounter){
		if(fscanf(inFile, "%u" "%u" "%u" "%u", &processArray[arrayCounter].priority,	//Reads file vars to uis
			&processArray[arrayCounter].cpu, &processArray[arrayCounter].io, &processArray[arrayCounter].ioTotal)!=4)
			printf("\nTHERE IS AN ERROR! in readFile.c\n");

		processArray[arrayCounter].curCpu = 0;	//Set all non-relevant vars to 0
		processArray[arrayCounter].curIo = 0;
		processArray[arrayCounter].wait = 0;
		processArray[arrayCounter].curPrior = processArray[arrayCounter].priority;
		processArray[arrayCounter].cpuTotal = 0;
		processArray[arrayCounter].ioTotal = 0;		//*
		processArray[arrayCounter].waitSum = 0;
		processArray[arrayCounter].waitCount = 0;
		processArray[arrayCounter].waitMin = 666666;
		processArray[arrayCounter].waitMax = 0;

		arrayCounter++;
	}
}


//Function to allocate memory for array of processes
//mallocs arrays of size elements
void getProcessArray(process* processArray, int size) {

		processArray = malloc(sizeof(process)*size);
}
