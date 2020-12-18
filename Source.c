
#include <stdio.h>
#include <stdlib.h>
#include "readFile.h"
#include "priorityQueue.h"
#include "a2.h"
#include "Source.h"

// Daniel Darcy
// CS 4540 HARDIN
// a2


//MAIN Description:
//Program runs a simulation of round robion data structure for operating system
//Size is entered in command line argument with fileName
//Wait time can be changed as neccesary througn var wait in first line of main
int main(int argc, char * argv[]) {

	ui size, wait=30, cpu=-1, RQueueCount=0, ioCount=0, quantumTime = 70, clockEnd=10000, clockCounter = 0;
	os system;	system.quantum = quantumTime;	system.wait=wait;		//FOR STATS
	char* fileName = argv[1];		//Set name
	sscanf(argv[2], "%u", &size);		//Set size
	process processArray[size];		//Array of processes
	ui readyQueue[size], ioWaiting[size];		//Index arrays for io and readyQueue
	getProcessArray(processArray, size);		//Memory Allocation for processArray
	readFile(fileName, size, processArray);		//ReadFile store in processArray

	for(int y=0; y<size; y++){	//Start with everything in ready queue
		pushRQ(processArray, readyQueue, RQueueCount, RQueueCount);
		RQueueCount++;
	}

	while(clockCounter < clockEnd){		//Clock Loop
		if(clockCounter == 0){
			processArray[0].priority = 0;
		}
		if(RQueueCount != 0){		//Check if readyQueue is empty
			sort(processArray, RQueueCount, readyQueue);		//Sort queue each clock tick
			updateRQueue(processArray, readyQueue, RQueueCount, wait);	//update RQ stats
		}
		if(cpu == -1 && RQueueCount != 0){		//if cpus empty fill it up
			popToCpu(processArray, readyQueue, &RQueueCount, &cpu);		//Fill empty cpu
		}
		if(cpu != -1){		//Check if cpu is empty
			updateCPU(processArray, &cpu, quantumTime, ioWaiting, &ioCount, readyQueue, &RQueueCount);		//updateCPU stats
		}
		updateWaitlist(processArray, ioWaiting, &ioCount, readyQueue, &RQueueCount);		//update waitlist stats
		clockCounter++;
	}			//End of clockLoop
	processArray[0].priority=0;
	printStats(processArray, system);
}


//cpu FUNCTIONS-------------------------------------------------------------------------
//Function fills cpu if nothing is in it, otherwise checks to see if the
//current process has reached cpuTime, or quantum time.
//If it has current process is removed to ioWaitlist and new process is added
//to the cpu from the ready queue.
void updateCPU(process processArray[], ui *cpu, ui timeQuantum, ui ioWaiting[],
	ui *waitlistCount, ui readyQueue[], ui *RQueueCount){

	if(processArray[*cpu].curCpu == processArray[*cpu].cpu){		//waitqueue io readyqueue
		popToWaitlist(ioWaiting, *cpu, waitlistCount);		//send to waitlist for io
		*waitlistCount = *waitlistCount + 1;
		processArray[*cpu].cpuTotal += processArray[*cpu].curCpu;
		processArray[*cpu].curCpu = 0;
		*cpu = -1;
	}
	else if(processArray[*cpu].curCpu == timeQuantum){	//straight back to ready queue
		processArray[*cpu].cpuTotal += processArray[*cpu].curCpu;
		processArray[*cpu].curCpu = 0;
		pushRQ(processArray, readyQueue, *RQueueCount, *cpu);
		*RQueueCount = *RQueueCount+1;
		if(processArray[*cpu].priority == 4294967295){
			processArray[*cpu].priority = 0;
			processArray[*cpu].curPrior = 0;
		}
		*cpu = -1;
	}		//then send directly to readyQueue \/
	else{
		processArray[*cpu].curCpu++;
	}
}


//Funtion pops processes from cpu to waitlist
void popToWaitlist(ui ioWaiting[], ui processArrayIndex, ui *waitlistCount){
	ioWaiting[*waitlistCount] = processArrayIndex;
	waitlistCount++;
}


//waitlist FUNCTIONS-----------------------------------------------------------------------------
//Function to update waitList
void updateWaitlist(process processArray[], ui ioWaiting[], ui *waitlistCount, ui readyQueue[], ui *RQLength){
	for(int r=0; r < *waitlistCount; r++){	//Update each array index
		processArray[ioWaiting[r]].curIo++;

		if(processArray[ioWaiting[r]].curIo == processArray[ioWaiting[r]].io){
			processArray[ioWaiting[r]].ioTotal += processArray[ioWaiting[r]].curIo;
			processArray[ioWaiting[r]].curIo = 0;

			popFromWaitlist(processArray, ioWaiting, r, readyQueue, *RQLength, waitlistCount);
			*RQLength = *RQLength + 1;
			*waitlistCount = *waitlistCount - 1;
		}
	}
}



//Function pops process from waitlist, either back to ready queue
int popFromWaitlist(process processArray[], ui ioWaiting[], ui waitArrayIndex, ui readyQueue[],
	 ui RQLength, ui *waitlistCount) {

		int retval = -1;
		//push back to RQ
		pushRQ(processArray, readyQueue, RQLength, ioWaiting[waitArrayIndex]);
		retval = 0;
		ioWaiting[waitArrayIndex] = -1;	//Set old value to -1
		//Move neccesary processes in waitlistArray up 1 index
		for(int k=waitArrayIndex; k < *waitlistCount; k++){
		 	swap(ioWaiting, k, k+1);
		}
		return retval;
}
