/*
dispatcher.c

Student Name : Abinav Bukkaraya
Student ID # : 0951030

Dispatch Algorithm : Round Robin
*/

#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 100

/*
Any required standard libraries and your header files here
*/
#include "process.h"
#include "resource.h"
#include "queue.h"


void getSimulationData(FILE* fd, Queue* newQueue);
int getNextArrivalTime(Queue* newQueue);



void dispatcher(FILE *fd, int quantum, int harddrive){
    // Tick Counter, this is the global time for the simulation
    int tickCounter = 0;

    // Create All Queues
    Queue *newQueue = createQueue(printProcess, deleteProcess, compareProcess);
    Queue *readyQueue = createQueue(printProcess, deleteProcess, compareProcess);
    Queue *pendQueue = createQueue(printProcess, deleteProcess, compareProcess);
    Queue *finishedQueue = createQueue(printProcess, deleteProcess, compareProcess);

    cpu CPU;
    hdd HDD;

    // Assign P0 to CPU
    Process *idleProcess = createProcess(0, 0, -1, NULL);

    CPU.proc = idleProcess;
    CPU.remainingTime = quantum;

    HDD.proc = idleProcess; 
    HDD.remainingTime = harddrive;

    getSimulationData(fd, newQueue);

    int nextArrivalTime = 0;

    // Simulation ends when all processes are finished
    // This means that there are no elements in any of the queues
    while(1) {
        nextArrivalTime = getNextArrivalTime(newQueue);

        // Add to ready queue if new process has arrived
        if (nextArrivalTime > 0 && tickCounter == nextArrivalTime) {
            insert(readyQueue, pop(newQueue));
        }

        int nextExchangeTime = -1;
        if(!queueEmpty(CPU.proc->exchangeTimes)) {
            int *exchangeTime = peek(CPU.proc->exchangeTimes);
            nextExchangeTime = *((int *) exchangeTime);
        }

        if (CPU.proc->cpuTime == nextExchangeTime) {
            deleteInt(pop(CPU.proc->exchangeTimes));
            insert(pendQueue, CPU.proc);

            CPU.proc = idleProcess;
        }

        if (CPU.proc->cpuTime == CPU.proc->runTime) {
            insert(finishedQueue, CPU.proc);
            CPU.proc = idleProcess;
        }

        if (HDD.remainingTime == 0 && HDD.proc->id != 0) {
            if (HDD.proc->runTime == HDD.proc->cpuTime) {
                insert(finishedQueue, HDD.proc);
            } else {
                insert(readyQueue, HDD.proc);
            }
            HDD.proc = idleProcess;
        }

        // Check if time quanta has been used up for the CPU
        if (CPU.remainingTime == 0 && CPU.proc->id != 0) {
            insert(readyQueue, CPU.proc);
            CPU.proc = idleProcess;
        }



        // Switch process if there are any in the ready queue, else continue running the current process

        if (CPU.proc->id == 0) {
            if(!queueEmpty(readyQueue)) {
                CPU.proc = pop(readyQueue);
            }

            CPU.remainingTime = quantum;
        }


        if (HDD.proc->id == 0) {
            if(!queueEmpty(pendQueue)) {
                HDD.proc = pop(pendQueue);
            }

            HDD.remainingTime = harddrive;
        }


        if(queueEmpty(newQueue) && queueEmpty(readyQueue) && queueEmpty(pendQueue)) {
            if(CPU.proc->id == 0 && HDD.proc->id == 0) {
                break;
            }
        }

        tickCounter++;
        CPU.remainingTime--;
        CPU.proc->cpuTime++;
        HDD.remainingTime--;

        updatePendTime(HDD.proc);

        // Increase time in readyQueue for all process
        batchProcessQueue(readyQueue, updateReadyTime);
        // Increase time in pendQueue for all process 
        batchProcessQueue(pendQueue, updatePendTime);
    }

    // printf("TC: %d\n", tickCounter);
    // printf("IDLE PROCESS:\n");
    printf("0 %d\n", idleProcess->cpuTime);
    // printf("Finished Queue:\n");
    printQueue(finishedQueue);

}


int getNextArrivalTime(Queue* newQueue) {
    if (queueEmpty(newQueue)) {
        return -1;
    }

    Process *proc = (Process *) peek(newQueue);

    return proc->arrivalTime;
} 



void getSimulationData(FILE* fd, Queue* newQueue) {
    char line_buffer[MAX_LINE_LENGTH];
    int start_time, run_time, process_id, num_exchanges, exchange_time;
    char *token;
    
    //Process simulation input line by line
    while (fgets(line_buffer, MAX_LINE_LENGTH, fd) != NULL && line_buffer[0] != '\n'){
        token = strtok(line_buffer, " ");
        sscanf(token, "%d",&start_time);
       
        token = strtok(NULL, " ");
        sscanf(token, "%d",&process_id);
        
        token = strtok(NULL, " ");
        sscanf(token, "%d",&run_time);
        
        num_exchanges = 0;
        token = strtok(NULL, " ");
        Queue *waitTimeQueue = createQueue(printInt, deleteInt, compareInt);
        while ( token != NULL ){
            num_exchanges += sscanf(token, "%d",&exchange_time);

            int *nextExchangeTime = malloc(sizeof(int));
            *nextExchangeTime = exchange_time;

            insert(waitTimeQueue, nextExchangeTime);

            token = strtok(NULL, " ");
        }

        Process *newProcess = createProcess(process_id, start_time, run_time, waitTimeQueue);
        insert(newQueue, newProcess); 
    }
}