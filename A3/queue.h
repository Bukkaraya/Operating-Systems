// Author: Abinav Bukkaraya
// ID: 0951030
// This code was written by the author in data structures course CIS 2520 Course in Fall 2017

/**
* @file queue.h
* @author Abinav Bukkaraya
* @date October 2017
* @brief File containing the function definitions of a Queue
*/
#include "linkedList.h"
#ifndef _QUEUE_
#define _QUEUE_


typedef struct Queue{
    List *list;
    int count;
    int hitCount;
} Queue;


/**Function to point the queue to the appropriate functions. Allocates memory to the struct.
*@return pointer to the queue
*@param printFunction function pointer to print a single node of the list
*@param deleteFunction function pointer to delete a single piece of data from the list
*@param compareFunction function pointer to compare two nodes of the list in order to test for equality or order
**/
Queue *createQueue(void (*printFunction) (void * toBePrinted),
void (*deleteFunction)(void *toBeDeleted), 
int (*compareFunction)(const void *first, const void *second));


/** Inserts data inside the queue base on it's priority
*@pre queue exists and has memory allocated to it. Node to be added is valid.
*@post The node to be added will be placed immediately before or after the first occurrence of a related node
*@param q pointer to the Queue
*@param data a pointer to data that is to be added to the queue
*@param priority the priority value of the data being added
**/
void insert(Queue *q, void *data);

/** Checks if queue is empty or not
*@pre queue exists and has memory allocated to it. Node to be added is valid.
*@param q pointer to the Queue
*@return 0 if queue is not empty and 1 if queue is empty
**/
int queueEmpty(Queue *q);

/** Removes the element at the top of the queue
*@pre queue exists and has memory allocated to it. Node to be added is valid.
*@param q pointer to the Queue
*@return pointer to the data that was removed from the queue or NULL if queue is empty
**/
void *pop(Queue *q);

/** Returns the element sitting at the top of the queue
*@pre queue exists and has memory allocated to it. Node to be added is valid.
*@param q pointer to the Queue
*@return pointer to data at the top or NULL if the queue is empty
**/
void *peek(Queue *q);

/** Destroys the queue and frees all memory
*@pre queue exists and has memory allocated to it. Node to be added is valid.
*@param q pointer to the Queue
**/
void destroyQueue(Queue *q);

/** Returns the number of elements in the queue
*@pre queue exists and has memory allocated to it. Node to be added is valid.
*@param q pointer to the Queue
@return count int
**/
int getCount(Queue *q);


void printQueue(Queue *q);

void batchProcessQueue(Queue *q, void (*updateFunction) (void * toBeUpdated));

void* searchQueue(Queue* q, void* item);

#endif