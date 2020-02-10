/*
dispatcher.c

Student Name : ....
Student ID # : ....

Dispatch Algorithm : ....
*/

#include <string.h>
#include <stddef.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 100

/*
Any required standard libraries and your header files here
*/
#include "process.h"
#include "cpu.h"
#include "queue.h"


void dispatcher(FILE *fd, int quantum, int harddrive){
    /*
        Your code here.
        You may edit the following code
    */

   // Create ALl Queues
   Queue *newQueue = createQueue(printProcess, deleteProcess, compareProcess);


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
        while ( token != NULL ){
            num_exchanges += sscanf(token, "%d",&exchange_time);
            token = strtok(NULL, " ");
        }

        Process *newProcess = createProcess(process_id, start_time, run_time, NULL);
        insert(newQueue, newProcess);

       printf("Process %3d wants to start at %6dms and run for %6dms and has %3d hard drive exchanges\n",  process_id, start_time, run_time, num_exchanges);    
    }

    printQueue(newQueue);
}
