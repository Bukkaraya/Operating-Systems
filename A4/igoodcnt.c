#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int NITER = 1000000;
sem_t counter_semaphore;
int cnt = 0;


void * Count(void * a)
{
    int i, tmp;

    for(i = 0; i < NITER; i++)
    {
        sem_wait(&counter_semaphore);
        tmp = cnt;      /* copy the global cnt locally */
        tmp = tmp+1;    /* increment the local copy */
        cnt = tmp;      /* store the local value into the global cnt */ 
        sem_post(&counter_semaphore);
    }
}

void exit_with_error(char* programName);



int main(int argc, char * argv[])
{
	pthread_t tid1, tid2;

	// validate arguments
    if(argc < 2) {
        fprintf(stderr, "Improper Arguments.\n");
        exit_with_error(argv[0]);
    }

    NITER = atol(argv[1]);

	if(NITER <= 0) {
		fprintf(stderr, "Enter a positive number.\n");
        exit_with_error(argv[0]);
	}

	// implementation
    sem_init(&counter_semaphore, 0, 1);

	// Parsing the arguments passed to your C program
	// Including the number of times that each thread increments
	// the shared count cnt
	// For example, NITER = 20000;
    


	// Display the number of times (entered by the user) that each thread
	// increments the shared count cnt
// PLEASE DO NOT remove or modify the following code 
	printf("2*NITER is [%d]\n", 2*NITER);
// End of code section 

	// creating Thread 1
	if(pthread_create(&tid1, NULL, Count, NULL))
	{
		fprintf(stderr, "Failed to create thread.\n");
        exit_with_error(argv[0]);
	}

	// creating Thread 2
	if(pthread_create(&tid2, NULL, Count, NULL))
	{
		fprintf(stderr, "Failed to create thread.\n");
        exit_with_error(argv[0]);
	}

	if(pthread_join(tid1, NULL))	/* wait for the thread 1 to finish */
	{
		fprintf(stderr, "Failed to join thread.\n");
        exit_with_error(argv[0]);
	}

	if(pthread_join(tid2, NULL))        /* wait for the thread 2 to finish */
	{
		fprintf(stderr, "Failed to join thread.\n");
        exit_with_error(argv[0]);
	}

        // Display the value of count cnt
// PLEASE DO NOT remove or modify the following code
	printf("\nCounter is [%d]\n", cnt);
	if (cnt == 2 * NITER) 
		printf("\nPASS\n");
	else
		printf("\nFAIL\n");
// End of code section

    sem_destroy(&counter_semaphore);
	pthread_exit(NULL);
}

void exit_with_error(char* programName) {
	fprintf(stderr, "usage: %s NoofTimesEachThreadIncrements\n", programName);
	fprintf(stderr, "Program exitted unsuccessfully.\n");
	exit(EXIT_FAILURE);
}

