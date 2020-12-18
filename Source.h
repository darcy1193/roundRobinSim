#ifndef SOURCE_H
#define SOURCE_H
#include "a2.h"

void updateCPU(process processArray[], ui *cpu, ui timeQuantum, ui ioWaiting[], ui *waitListCount,
	ui readyQueue[], ui *RQueueCount);

void clockLoop(process processArray[], ui processArraySize);

void popToWaitlist(ui ioWaiting[], ui processArrayIndex, ui *waitlistCount);

void updateWaitlist(process processArray[], ui ioWaiting[], ui *waitlistCount, ui readyQueue[], ui *RQLength);

int popFromWaitlist(process processArray[], ui ioWaiting[], ui waitArrayIndex, ui readyQueue[],
	 ui RQLength, ui *waitlistCount);
#endif
