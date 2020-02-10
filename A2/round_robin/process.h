#include "queue.h"
#ifndef _PROCESS_
#define _PROCESS_

typedef struct Process
{
    int id;
    int arrivalTime;
    int readyTime;
    int blockedTime;
    int cpuTime;
    int runTime;
    int numWaitTimes;
    int remainingRunTime;
    Queue *exchangeTimes;
} Process;

Process* createProcess(int id, int arrivalTime, int runTime, Queue* exhangeTimes);
int getTotalRunTime(Process *proc);
void printProcess(void *p);
void deleteProcess(void *p);
int compareProcess(const void* p1, const void* p2);
void printInt(void* d);
int compareInt(const void* a, const void* b);
void deleteInt(void *d);


#endif