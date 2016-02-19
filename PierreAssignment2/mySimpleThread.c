#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

int SharedVariable = 0;

void * SimpleThread(void * ptr) {
	int num, val;
	int threadID = (int) ptr;
	
	for(num = 0; num < 20; num++) {
		if (random() > RAND_MAX / 2)
			usleep(10);
	
		val = SharedVariable;
		printf("*** thread %d sees value %d\n", threadID, val);
		SharedVariable = val + 1;
		}
	val = SharedVariable;
	printf("Thread %d sees final value %d\n", threadID, val);
	return NULL;
}

int main(int argc, char *argv[]){
	int i;
	if(argc == 1){
		printf("You need to input a number of threads\n");
		return 1;
	}
	
	int numThreads = atoi(argv[1]);	
	pthread_t myThreads[numThreads];
	
	for(i=0; i<numThreads; i++){
		if(pthread_create(&myThreads[i], NULL, SimpleThread, (void *) i) !=0 ) 
		{
      		perror("SimpleThread creation failed!\n");
      		exit(0);
    	}
	}
	while(1);
	return 0;
}

