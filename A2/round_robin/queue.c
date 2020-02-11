#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"


Queue *createQueue(void (*printFunction) (void * toBePrinted),
    void (*deleteFunction)(void *toBeDeleted), 
    int (*compareFunction)(const void *first, const void *second)){

    Queue *q = malloc(sizeof(Queue));
    q->list = initializeList(printFunction, deleteFunction, compareFunction);
    q->count = 0;

    return q;
}


void insert(Queue *q, void *data){
    if(q == NULL){
        return;
    }

    insertFront(q->list, data);
    q->count++;
}


int queueEmpty(Queue *q){
    if(q != NULL){
        return isEmpty(q->list);
    }

    return 1;
}


void *pop(Queue *q){
    if(q == NULL){
        return NULL;
    }

    if(!queueEmpty(q)){
        void *last = peek(q);
        void *data = deleteNodeFromList(q->list, last);
        if(data != NULL){
            q->count--;
        }
        return data;
    }

    return NULL;
}


void *peek(Queue *q){
    if(!queueEmpty(q)){
        return getFromBack(q->list);
    }
    return NULL;
}


void destroyQueue(Queue *q){
    if(q != NULL){
        if(q->list != NULL){
            deleteList(q->list);
        }
        free(q);
    }
}


int getCount(Queue *q){
    if (q != NULL) {
        return q->count;
    }
    
    return 0;
}


void printQueue(Queue *q) {
    printBackwards(q->list);
}


void batchProcessQueue(Queue *q, void (*updateFunction) (void * toBeUpdated)) {
    if (q == NULL) {
        return;
    }

    batchProcessList(q->list, updateFunction);
}