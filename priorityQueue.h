#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "a2.h"

 void pushRQ(process processArray[], ui readyQueue[], ui readyQueueLength, int timeCounter);
 void popToCpu(process processArray[], ui readyQueue[], ui *readyQueueLength, ui *cpu);
 void sort(process processArray[], int size, ui readyQueue[]);
 void updateRQueue(process processArray[], ui readyQueue[], ui readyQueueLength, ui wait);
 void swap(ui readyQueue[], int index1, int index2);

 #endif
