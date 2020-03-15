// Abinav Bukkaraya
// ID: 0951030
// Assignment 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

// Memory and Page Table Configurations
#define MAX_ARRAY_LEN 10000
#define TLB_SIZE 16
#define NUM_PAGES 256
#define NUM_FRAMES 256
#define PAGE_SIZE 256
#define FRAME_SIZE 256
#define MAX_MEMORY_SIZE 65536 

#define TRUE 1
#define FALSE 0


// Struct Definitions
typedef struct pageDetails{
    int pageNumber;
    int offset;
} PageDetails;


typedef struct pagetablecell
{
    int frameNumber;
    int isValid;
} PageTableCell;

typedef struct memory {
    char cells[MAX_MEMORY_SIZE];
    int pointer;
} Memory;


typedef struct tlbcell {
    int frameNumber;
    int pageNumber;
} TLBCell;


// General Helper Functions

// Get the page number and offset for a given address
PageDetails getPageDetails(int address);

// Open backing storage for reading
FILE* getBackingStorage(char* fileName);

// Retrieve page from the backing storage and place it in memory, update page table with new frame
void fetchPage(FILE* storage, Memory* memory, int pageNumber, PageTableCell pageTable[]);

// Get value from physical memory given a physical address
char getValueFromMemory(int address, Memory* memory);

// Get frame number given page number from TLB/Page Table
int getFrameAddress(int pageNumber, PageTableCell pageTable[], Queue* TLB);

// TLB Cell Helper Functions

// Print Value in TLB
void printTLBCell(void* data);

// Comparision function for TLB Cells
int compareTLBCell(const void* a, const void* b);

// Free allocated memory for a TLB Cell
void deleteTLBCell(void* data);

// Create a TLB Cell
TLBCell* createTLBCell(int pageNumber, int frameNumber);

// Check if the TLB is full
int isTLBFull(Queue* TLB);

// Exit program with failure in the case of an error
void exit_with_failure(char* programName);



int main(int argc, char* argv[]) {

    PageTableCell pageTable[NUM_PAGES] = {{0}};

    if(argc < 2) {
        fprintf(stderr, "No file given.\n");
        exit_with_failure(argv[0]);
    }

    FILE* fp = NULL;
    fp = fopen(argv[1], "r");

    if(fp == NULL) {
        fprintf(stderr, "Invalid File.\n");
        exit_with_failure(argv[0]);
    }


    // Allocate Memory
    Memory* memory = malloc(sizeof(Memory));
    memory->pointer = 0;

    // TLB Allocation
    Queue* TLB = createQueue(printTLBCell, deleteTLBCell, compareTLBCell);

    // Check for proper args



    int addresses[MAX_ARRAY_LEN];
    int numAddresses = 0;

    // Get number of addresses and store in an array
    while(fscanf(fp, "%d", &addresses[numAddresses]) == 1) {
        numAddresses++;
    }

    fclose(fp);

    // Obtain backing storage
    char* storageFileName = "BACKING_STORE.bin";
    FILE* backingStorage = getBackingStorage(storageFileName);

    int numPageFaults = 0;
    char valueAtAddress = '\0';
    int physicalAddress = 0;

    // Begin main simulation loop
    for(int i = 0; i < numAddresses; i++) {
        PageDetails pageDetails = getPageDetails(addresses[i]);
        
        // Check for a page fault
        if(pageTable[pageDetails.pageNumber].isValid == FALSE) {
            numPageFaults++;
            // Fetch the page and put it in the memory for a page fault
            fetchPage(backingStorage, memory, pageDetails.pageNumber, pageTable);
        }

        physicalAddress = getFrameAddress(pageDetails.pageNumber, pageTable, TLB) + pageDetails.offset;
        valueAtAddress = getValueFromMemory(physicalAddress, memory);
        
        printf("Virtual address: %d Physical address: %d Value: %d\n", addresses[i], physicalAddress, valueAtAddress);
    }

    printf("Number of Translated Address = %d\n", numAddresses);
    fprintf(stderr, "Page Faults = %d\n", numPageFaults);
    fprintf(stderr, "Page Fault Rate = %.3f\n", (float) numPageFaults / numAddresses);
    fprintf(stderr, "TLB Hits = %d\n", TLB->hitCount);
    fprintf(stderr, "TLB Hit Rate = %.3f\n", (float) TLB->hitCount / numAddresses);

    // Free allocated memory
    free(memory);
    fclose(backingStorage);
    destroyQueue(TLB);

    return 0;
}

void exit_with_failure(char* programName) {
    fprintf(stderr, "usage: %s filenameoflogicaladdresses\n", programName);
    fprintf(stderr, "Program terminated unsuccessfully.\n");
    exit(EXIT_FAILURE);
}


int getFrameAddress(int pageNumber, PageTableCell pageTable[], Queue* TLB) {
    // Check if TLB has the value and if it doesn't load it into the TLB
    TLBCell* cellToSearch = createTLBCell(pageNumber, 0);
    TLBCell* foundItem = (TLBCell *) searchQueue(TLB, cellToSearch);

    int frameNumber = 0;

    // Check if the item is in TLB
    if(foundItem == NULL) {
        // Add value to TLB and use FIFO replacement if TLB is full
        if(isTLBFull(TLB)) {
            void* cell = pop(TLB);
            deleteTLBCell(cell);
        }

        frameNumber = pageTable[pageNumber].frameNumber;
        cellToSearch->frameNumber = frameNumber;
        
        insert(TLB, cellToSearch); 
    } else {
        // Get value from TLB and count the TLB hit
        frameNumber =  foundItem->frameNumber;
        TLB->hitCount++;
        free(cellToSearch);
    }

    return frameNumber;
}

char getValueFromMemory(int address, Memory* memory) {
    return memory->cells[address];
}


void fetchPage(FILE* storage, Memory* memory, int pageNumber, PageTableCell pageTable[]) {
    int fileOffset = pageNumber * PAGE_SIZE;
    fseek(storage, 0, SEEK_SET);
    fseek(storage, fileOffset, SEEK_SET);
    int frameNumber = memory->pointer * FRAME_SIZE;

    char* buffer = malloc(sizeof(char) * PAGE_SIZE);

    fread(buffer, sizeof(char), PAGE_SIZE, storage);

    for(int i = 0; i < PAGE_SIZE; i++) {
        memory->cells[frameNumber + i] = buffer[i];
    }

    memory->pointer++;

    // Set frame number and frame as valid
    pageTable[pageNumber].frameNumber = frameNumber;
    pageTable[pageNumber].isValid = TRUE;

    free(buffer);

    return;
}


PageDetails getPageDetails(int address) {
    int pageNumber = 0;
    int offset = 0;
    int maskedAddress = 0;

    PageDetails details;
    // 16 bit logical address contains 8 bit page number and 8 bit offset
    maskedAddress = address & 0x0000ffff;
    pageNumber = maskedAddress >> 8;
    offset = maskedAddress & 0x000000ff;
    details.pageNumber = pageNumber;
    details.offset = offset;

    return details;
}


FILE* getBackingStorage(char* fileName) {
    FILE* fp = fopen(fileName, "rb");
    if(fp == NULL) {
        exit(EXIT_FAILURE);
    }

    return fp;
}

// TLB Helper Function Definitions
void printTLBCell(void* data) {
    if (data == NULL) {
        return;
    }

    TLBCell* cell = (TLBCell *) data;

    printf("TLB<Frame: %d, Page: %d>", cell->frameNumber, cell->pageNumber);
}


TLBCell* createTLBCell(int pageNumber, int frameNumber) {
    TLBCell* newCell = malloc(sizeof(TLBCell));
    newCell->pageNumber = pageNumber;
    newCell->frameNumber = frameNumber;

    return newCell;
}


int compareTLBCell(const void* a, const void* b) {
    if(a == NULL || b == NULL) {
        return -1;
    }

    TLBCell* c1 = (TLBCell *) a;
    TLBCell* c2 = (TLBCell *) b;

    if(c1->pageNumber > c2->pageNumber) {
        return 1;
    } else if(c1->pageNumber < c2->pageNumber) {
        return -1;
    }

    return 0;
}


void deleteTLBCell(void* data) {
    if(data == NULL) {
        return;
    }

    free(data);
}

int isTLBFull(Queue* TLB) {
    if(TLB->count >= TLB_SIZE) {
        return TRUE;
    }

    return FALSE;       
}