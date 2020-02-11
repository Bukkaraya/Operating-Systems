#include "process.h"

#ifndef _RESOURCE_
#define _RESOURCE_

typedef struct cpu {
    Process* proc;
    int remainingTime;
} cpu;

typedef struct hdd {
    Process* proc;
    int remainingTime;
} hdd;

#endif