// Author: Abinav Bukkaraya
// ID: 0951030
// This code was written by the author in data structures course CIS 2520 Course in Fall 2017

#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"


List *initializeList(void (*printFunction) (void * toBePrinted), void (*deleteFunction)(void *toBeDeleted), int (*compareFunction)(const void *first, const void *second)){
    List *l = malloc(sizeof(List));
    
    if (l != NULL) {
        l->head = NULL;
        l->tail = NULL;
        l->deleteNode = deleteFunction;
        l->compare = compareFunction;
        l->printNode = printFunction;
    }

    return l;
}


Node *initializeNode(void *data){
    Node *n = malloc(sizeof(Node));
    
    if (n != NULL) {
        n->data = data;
        n->previous = NULL;
        n->next = NULL;
    }
    
    return n;
}


void insertFront(List *list, void *toBeAdded){
    Node *n = initializeNode(toBeAdded);
    if (list->head == NULL && list->tail == NULL) {
        list->head = n;
        list->tail = n;
    } else {
        Node *temp = list->head;
        temp->previous = n;
        n->next = temp;
        list->head = n;
    }
}


void insertBack(List *list, void *toBeAdded){
    Node *n = initializeNode(toBeAdded);
    if (list->head == NULL && list->tail == NULL) {
        list->head = n;
        list->tail = n;
    } else {
        Node *temp = list->tail;
        temp->next = n;
        n->previous = temp;
        list->tail = n;
    }
}


void deleteList(List *list){
    Node *cur = list->head;
    while (cur != NULL) {
        list->head = cur->next;
        list->deleteNode(cur->data);
        free(cur);
        cur = list->head;
    }
    free(list);
}


void *getFromFront(List *list){
    if(list != NULL){
        if(list->head != NULL){
            return list->head->data;
        }
    }

    return NULL;
}


void *getFromBack(List *list){
    if(list != NULL){
        Node *t = list->head;
        while(t->next != NULL){
            t = t->next;
        }
        return t->data;
    }

    return NULL;
}


void printForward(List *list){
    if(list != NULL){
        if(list->head == NULL){
            return;
        }else{
            Node *cur = list->head;
            while(cur != NULL){
                list->printNode(cur->data);
                cur = cur->next;
            }
        }
    }
}


void printBackwards(List *list){
    if(list != NULL){
        if(list->tail == NULL){
            printf("List is empty.");
        }else{
            Node *cur = list->tail;
            while(cur != NULL){
                list->printNode(cur->data);
                cur = cur->previous;
            }
        }
    }
}

void* searchList(List *list, void* item) {
    if(list == NULL || list->head == NULL) {
        return NULL;
    }

    if(item == NULL) {
        return NULL;
    }

    Node *currentNode = list->head;

    while(currentNode != NULL) {
        if(list->compare(currentNode->data, item) == 0) {
            return currentNode->data;
        }

        currentNode = currentNode->next;
    }

    return NULL;
}

void *deleteNodeFromList(List *list, void *toBeDeleted){
    if(list->head == NULL || toBeDeleted == NULL){
        return NULL;
    }

    Node *cur = list->head;
    
    while(cur != NULL){
        if(list->compare(cur->data, toBeDeleted) == 0){
            //list->deleteNode(cur->data);
            
            if(cur->previous == NULL && cur->next == NULL){
                list->head = NULL;
                list->tail = NULL;
            }else if(cur->previous == NULL){
                cur->next->previous = NULL;
                list->head = cur->next;
            }else if(cur->next == NULL){
                cur->previous->next = NULL;
                list->tail = cur->previous;
            }else{
                cur->next->previous = cur->previous;
                cur->previous->next = cur->next;
            }
            
            void *data = cur->data;
            cur->data = NULL;
            free(cur);

            return data;
        }
        cur = cur->next;
    }

    return NULL;

}

int isEmpty(List *list){
    if(list->head == NULL){
        return 1;
    }
    return 0;
}


void batchProcessList(List *list, void (*updateFunction) (void * toBeUpdated)) {
    if (list == NULL) {
        return;
    }

    Node *currentNode = list->head;

    while(currentNode != NULL) {
        updateFunction(currentNode->data);

        currentNode = currentNode->next;
    }
}