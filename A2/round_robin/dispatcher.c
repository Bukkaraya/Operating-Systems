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
#include "cpu.h"
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

    cpu CPU;

    // Assign P0 to CPU
    Process *idleProcess = createProcess(0, 0, 0, NULL);

    CPU.proc = idleProcess;
    CPU.remainingTime = quantum;

    getSimulationData(fd, newQueue);

    int nextArrivalTime = 0;

    // Simulation ends when all processes are finished
    // This means that there are no elements in any of the queues
    while(!queueEmpty(newQueue) || !queueEmpty(readyQueue) || !queueEmpty(pendQueue)) {
        nextArrivalTime = getNextArrivalTime(newQueue);

        // Add to ready queue if new process has arrived
        if (nextArrivalTime > 0 && tickCounter == nextArrivalTime) {
            insert(readyQueue, pop(newQueue));
        }

        // Check if time quanta has been used up for the CPU
        if (CPU.remainingTime == 0) {
            insert(readyQueue, CPU.proc);
            CPU.proc = idleProcess;
        }  

        // Switch process if there are any in the ready queue, else continue running the current process

        if (CPU.proc->id == 0) {
            if(!queueEmpty(readyQueue)) {
                insert(readyQueue, CPU.proc);
                CPU.proc = pop(readyQueue);
            }

            CPU.remainingTime = quantum;
        }


        tickCounter++;
        CPU.remainingTime--;
        CPU.proc->remainingRunTime--;
        CPU.proc->cpuTime++;

        if(tickCounter == 1000) {
            break;
        }
    }

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