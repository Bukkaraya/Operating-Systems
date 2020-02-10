#include <stdio.h>
#include <stdlib.h>
#include "process.h"


Process* createProcess(int id, int arrivalTime, int runTime, Queue* exhangeTimes) {
    Process *proc = malloc(sizeof(Process));
    proc->id = id;
    proc->arrivalTime = arrivalTime;
    proc->runTime = runTime;

    return proc;
}


int getTotalRunTime(Process *p) {
    int totalRunTime = 0;
    totalRunTime += p->cpuTime;
    totalRunTime += p->readyTime;
    totalRunTime += p->blockedTime;

    return totalRunTime;
}

void printProcess(void* p) {
    Process *proc = (Process *) p;
    printf("Process<ID: %d, AT: %d, RT: %d>\n", proc->id,
        proc->arrivalTime, proc->runTime);
}

void deleteProcess(void *p) {
    if (p != NULL) {
        free(p);
    }
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