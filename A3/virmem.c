// Abinav Bukkaraya
// ID: 0951030
// Assignment 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY_LEN 1000
#define MAX_TLB_LEN 16
#define NUM_PAGES 256
#define NUM_FRAMES 256
#define PAGE_SIZE 256
#define FRAME_SIZE 256
#define MAX_MEMORY_SIZE 65536 

#define TRUE 1
#define FALSE 0


typedef struct pageDetails{
    int pageNumber;
    int offset;
} PageDetails;


typedef struct frame {
    int* cell;
} Frame;

typedef struct pagetablecell
{
    int frameNumber;
    int isValid;
} PageTableCell;

typedef struct memory {
    char cells[MAX_MEMORY_SIZE];
    int pointer;
} Memory;



PageDetails getPageDetails(int address);
FILE* getBackingStorage(char* fileName);
void fetchPage(FILE* storage, Memory* memory, int pageNumber, PageTableCell pageTable[]);
char getValueFromMemory(int address, Memory* memory);
int getFrameAddress(int pageNumber, PageTableCell pageTable[]);


int main(int argc, char* argv[]) {

    PageTableCell pageTable[NUM_PAGES] = {0};
    Memory* memory = malloc(sizeof(Memory));
    memory->pointer = 0;

    if(argc < 2) {
        // TODO: Print this to stderr
        printf("Please enter a proper file name.\n");
        return 0;
    }

    FILE* fp = NULL;

    fp = fopen(argv[1], "r");

    if(fp == NULL) {
        // TODO: Print this to stderr
        printf("Could not open the file.\n");
        exit(EXIT_FAILURE);
    }

    int addresses[MAX_ARRAY_LEN];
    int numAddresses = 0;

    while(fscanf(fp, "%d", &addresses[numAddresses]) == 1) {
        numAddresses++;
    }

    fclose(fp);

    char* storageFileName = "BACKING_STORE.bin";

    FILE* backingStorage = getBackingStorage(storageFileName);

    int numPageFaults = 0;
    int memoryPointer = 0;
    char valueAtAddress = '\0';
    int physicalAddress = 0;

    // Begin main simulation loop
    for(int i = 0; i < numAddresses; i++) {
        PageDetails pageDetails = getPageDetails(addresses[i]);

        if(pageTable[pageDetails.pageNumber].isValid == FALSE) {
            numPageFaults++;
            // Fetch the page and put it in the memory
            fetchPage(backingStorage, memory, pageDetails.pageNumber, pageTable);
        }

        physicalAddress = getFrameAddress(pageDetails.pageNumber, pageTable) + pageDetails.offset;
        valueAtAddress = getValueFromMemory(physicalAddress, memory);
        
        printf("Virtual address: %d Physical address: %d Value: %d\n", addresses[i], physicalAddress, valueAtAddress);
    }

    printf("Number of Page Faults: %d\n", numPageFaults);

    fclose(backingStorage);

    return 0;
}

int getFrameAddress(int pageNumber, PageTableCell pageTable[]) {
    return pageTable[pageNumber].frameNumber;
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
