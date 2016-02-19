#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "simple.h"

#define PTHREAD_SYNC

int SharedVariable = 0;

#ifdef PTHREAD_SYNC
pthread_mutex_t sharedVarLock = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barr;
#endif

void* SimpleThread (void* s) {
	int num, val;

	int id = (intptr_t) s;

	for (num = 0; num < 20; num++) {
		if (random() > RAND_MAX / 2) {
			usleep(10);
		}
#ifdef PTHREAD_SYNC
		pthread_mutex_lock(&sharedVarLock);
#endif
		val = SharedVariable;
		printf("*** thread %d sees value %d\n", id, val);
		SharedVariable = val + 1;
#ifdef PTHREAD_SYNC
		pthread_mutex_unlock(&sharedVarLock);
#endif
	}

#ifdef PTHREAD_SYNC
	int rc = pthread_barrier_wait(&barr);
	if (rc != 0 && rc != PTHREAD_BARRIER_SERIAL_THREAD)
	{
		printf("Could not wait on barrier\n");
		exit(-1);
	}
#endif
	val = SharedVariable;

	printf("Thread %d sees final value %d\n", id, val);
	pthread_exit(NULL);
	return NULL;
}

int main (int argc, char *argv[]) {
	// Takes one argument: int numberOfThreads

	if (argc != 2) {
		printf("Usage: ./simple <# of threads>.\n");
		return 0;
	}

	int numberOfThreads = atoi(argv[1]);

	if (numberOfThreads == 0) {
		printf("Invalid input paramater.\n");
		return 0;
	}

#ifdef PTHREAD_SYNC
    if(pthread_barrier_init(&barr, NULL, numberOfThreads))
    {
        printf("Could not create a barrier\n");
        return -1;
    }
#endif

	pthread_t threads[numberOfThreads];

	printf("Number of threads: %d\n", numberOfThreads);


	// init the pthreds
	for (int i = 0; i < numberOfThreads; i++) {
		if (pthread_create(&threads[numberOfThreads], NULL, SimpleThread, (void *)(intptr_t)i) != 0) {
			perror("SimpleThread could not be created!\n");
			exit(0);
		}
	}

	pthread_exit(0);

	return 0;
}