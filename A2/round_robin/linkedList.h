// Author: Abinav Bukkaraya
// ID: 0951030
// This code was written by the author in data structures course CIS 2520 Course in Fall 2017

/**
* @file LinkedListAPI.h
* @author Abinav Bukkaraya
* @date October 2017
* @brief File containing the function definitions of a doubly linked list
This is from my implementation of linked list from the Fall 2017 Data Structures course.
*/

#ifndef _LIST_API_
#define _LIST_API_


/**
*Node of a linked list. This list is doubly linked, meaning that it has points to both the node immediately in front 
of it, as well as the node immediately behind it.
**/
typedef struct listNode{
    void *data;
    struct listNode *previous;
    struct listNode *next;
} Node;

/**
*Dummy head of the list. Contains no actual data on it beyond a pointer to the front and end of the list.
**/
typedef struct listHead{
    Node *head;
    Node *tail;
    void (*deleteNode)(void *toBeDeleted);
    int (*compare)(const void *first,const void *second);
    void (*printNode)(void *toBePrinted);
} List;

/**Function to point the list head to the appropriate functions. Allocates memory to the struct.
*@return pointer to the list head
*@param printFunction function pointer to print a single node of the list
*@param deleteFunction function pointer to delete a single piece of data from the list
*@param compareFunction function pointer to compare two nodes of the list in order to test for equality or order
**/
List *initializeList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second));

/**Function for creating a node for a linked list. This node contains generic data and may be connected to 
other notes in a list.
*@pre data should be of same size of void pointer on the users machine to avoid size conflicts. data must be valid.
*data must be cast to void pointer before being added.
*@post data is valid to be added to a linked list
*@return On success returns a node that can be added to a linked list. On failure, returns NULL.
*@param data - is a generic pointer to any data type.
**/
Node *initializeNode(void *data);

/**Inserts a Node to the front of a linked list. The list then updates accordingly to adhere to the ADT.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the dummy head of the list
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertFront(List *list, void *toBeAdded);

/**Inserts a Node to the back of a linked list. The list then updates accordingly to adhere to the ADT.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the dummy head of the list
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertBack(List *list, void *toBeAdded);

/** Deletes the entire linked list head to tail, starting with the nodes, followed by the list itself.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the List-type dummy node
**/
void deleteList(List *list);

/**Function to remove a node from the list and alter the pointers accordingly to not disrupt the order of the 
*data structure. 
*@pre List must exist and have memory allocated to it
*@post toBeDeleted will have its memory freed if it exists in the list.
*@param list pointer to the dummy head of the list containing deleteFunction function pointer
*@param toBeDeleted pointer to data that is to be removed from the list
*@return returns pointer to data that was deleted or NULL if data was not found or list is empty
**/
void *deleteNodeFromList(List *list, void *toBeDeleted);

/**Function to return the data at the front of the list.
*@pre The list exists and has memory allocated to it
*@param list pointer to the dummy head of the list containing the head of the list
*@return pointer to the data located at the head of the list
**/
void *getFromFront(List *list);

/**Function to return the data at the back of the list.
*@pre The list exists and has memory allocated to it
*@param list pointer to the dummy head of the list containing the tail of the list
*@return pointer to the data located at the tail of the list
**/
void *getFromBack(List *list);

/**Function to print list from head to tail. This will utilize the list's printNode function pointer to print.
*@pre List must exist, but does not have to have elements.
*@param list Pointer to linked list dummy head.
**/
void printForward(List *list);

/**Function to print list from tail to head. This will utilize the list's printNode function pointer to print.
*@pre List must exist, but does not have to have elements.
*@param list Pointer to linked list dummy head.
**/
void printBackwards(List *list);


int isEmpty(List *list);


void batchProcessList(List *list, void (*updateFunction) (void * toBeUpdated));


#endif