#include <stdio.h>
#include <stdlib.h>
#include "process.h"


Process* createProcess(int id, int arrivalTime, int runTime, Queue* exhangeTimes) {
    Process *proc = malloc(sizeof(Process));
    proc->id = id;
    proc->arrivalTime = arrivalTime;
    proc->runTime = runTime;
    proc->exchangeTimes = exhangeTimes;
    proc->numWaitTimes = getCount(proc->exchangeTimes);

    return proc;
}


int getTotalRunTime(Process *p) {
    int totalRunTime = 0;
    totalRunTime += p->cpuTime;
    totalRunTime += p->readyTime;
    totalRunTime += p->pendTime;

    return totalRunTime;
}

void printInt(void* d) {
    int value = *((int *) d);
    printf("Wait Time: %d\n", value);
}

void deleteInt(void *d) {
    if(d != NULL) {
        free(d);
    }
}


int compareInt(const void* a, const void* b) {
    int num1 = *((int *) a);
    int num2 = *((int *) b);

    if (num1 > num2) {
        return 1;
    } else if (num1 == num2) {
        return 0;
    } else {
        return -1;
    }
}


void printProcess(void* p) {
    Process *proc = (Process *) p;
    printf("%d %d %d %d\n", proc->id,
        proc->cpuTime, proc->readyTime, proc->pendTime);
}

void deleteProcess(void *p) {
    if (p != NULL) {
        Process *proc = (Process *) p;
        destroyQueue(proc->exchangeTimes);
        free(p);
    }
    // Add delete for wait time queue as well
}

int compareProcess(const void* p1, const void* p2) {
    Process *proc1 = (Process *) p1;
    Process *proc2 = (Process *) p2;

    if (proc1->id > proc2->id) {
        return 1;
    } else if (proc1->id == proc2->id) {
        return 0;
    } else {
        return -1;
    }
}

void updateReadyTime(void *p) {
    if (p == NULL) {
        return;
    }

    Process *proc = (Process *) p;
    proc->readyTime++;
}


void updatePendTime(void *p) {
    if (p == NULL) {
        return;
    }

    Process *proc = (Process *) p;
    proc->pendTime++;
}