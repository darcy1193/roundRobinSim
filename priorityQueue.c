#include <stdio.h>
#include <stdlib.h>
#include "priorityQueue.h"
#include "a2.h"

//Function adds to the back of the line
void pushRQ(process processArray[], ui readyQueue[], ui readyQueueLength, int timeCounter){
	readyQueue[readyQueueLength] = timeCounter;
	processArray[readyQueue[readyQueueLength]].waitCount++;
	//readyQueueLength++;
}

//Function removes from front of line of ReadyQueue
void popToCpu(process processArray[], ui readyQueue[], ui *readyQueueLength, ui *cpu){

	if(processArray[readyQueue[0]].waitMin > processArray[readyQueue[0]].wait){
		processArray[readyQueue[0]].waitMin = processArray[readyQueue[0]].wait;
	}		//compare waitmin with wait
	if(processArray[readyQueue[0]].waitMax < processArray[readyQueue[0]].wait){
		processArray[readyQueue[0]].waitMax = processArray[readyQueue[0]].wait;
	}		//compare waitmax with waitmax

	//Update waitSum
	processArray[readyQueue[0]].waitSum += processArray[readyQueue[0]].wait;
	processArray[readyQueue[0]].wait = 0;
	processArray[readyQueue[0]].curPrior = processArray[readyQueue[0]].priority;
	*cpu = readyQueue[0];		//put in cpu
	readyQueue[0] = -1;		//set to -1 (remove)

	//Move all processes in readyQueueArray up 1 index
	for(int k=0; k < *readyQueueLength; k++){
		swap(readyQueue, k, k+1);
	}
	*readyQueueLength = *readyQueueLength-1;		//change length
}

//Function to resort readyQueue based on priority
//Algortithm specs found at https://www.geeksforgeeks.org/insertion-sort/
void sort(process processArray[], int size, ui readyQueue[]){
	/* Function to sort an array using insertion sort*/
	int i, key, j;
	for (i = 1; i < size; i++){
		//printf("\nhere17 + %d\n", processArray[readyQueue[46]].curPrior);
		key = processArray[readyQueue[i]].curPrior;
		j = i-1;
		//Move elements ofprocessArray[0..i-1], that are greater than key, to one position ahead
		while (j >= 0 && processArray[readyQueue[j]].curPrior < key){
			swap(readyQueue, j, j+1);
			j = j-1;
		}
		processArray[readyQueue[j+1]].curPrior = key;
	}
}

//Function to update queue after each clock iteration
void updateRQueue(process processArray[], ui readyQueue[], ui readyQueueLength, ui wait){
	for (int z=0; z<readyQueueLength; z++){
		processArray[readyQueue[z]].wait++;

		if(processArray[readyQueue[z]].wait == wait && processArray[readyQueue[z]].priority < 15){
			processArray[readyQueue[z]].curPrior++;		//increase priority
			//printf("\npriority increased for index %d\n", readyQueue[z]);
			//printf("\n rql=%d\n", readyQueueLength);
		}
	}
}

//Function to swap processArray processes by indexes, used for sort
void swap(ui readyQueue[], int index1, int index2){
	int temp = readyQueue[index1];
	readyQueue[index1] = readyQueue[index2];
	readyQueue[index2] = temp;
}
