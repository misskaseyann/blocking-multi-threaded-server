#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

/* 
 * NOTE:
 * This server only supports a MAX number of threads.
 * If the number of threads exceeds MAX at once (worst case scenario)
 * then unpredictable behavior may occur.
 * Adjust the MAX value based on the use case.
 */
#define MAX_THREADS 30

int numFiles = 0; //keeps count of files dealt with

/*
 * Lab Assignment 4
 * Blocking Multi-threaded Server
 *
 * @authors Kasey Stowell, Kehlsey Lewis
 * @version Fall 2018
 *
 */

void* fileget(void* arg);
void sigUsrHandler(int signNum);

int main() {
	pthread_t threads[MAX_THREADS];
	int status;
	char input[256];
	char* inputstr = input;
	int counter = 0; // count spot in threads

	signal(SIGINT, sigUsrHandler); //creating SIGINT for termination
	
	// dispatcher reads user input, creates thread, detaches thread, and repeats
	while(1) {
		
		// get user information
		printf("\nEnter File Name: ");
		scanf("%s", inputstr);

			// create worker thread
			if ((status = pthread_create(&threads[counter], NULL, fileget, (void*)inputstr)) != 0) {
				fprintf(stderr, "thread create error %d: %s\n", status, strerror(status));
				exit(1);
			}

		// detach the child to execute independently until termination
			if ((status = pthread_detach (threads[counter])) != 0) {
				fprintf(stderr, "thread detach error %d: %s\n", status, strerror(status));
				exit(1);
			}

		// update counter
			counter < MAX_THREADS ? (counter++) : (counter = 0);		
	}
	return 0;

}

void* fileget(void* arg) {
	char* str = malloc(strlen((char*) arg) + 1);
	strcpy(str, (char*) arg);
	srand(time(NULL));

	// generate 80/20 probability for sleep time
	float ran = (float)rand()/RAND_MAX;
	ran <= 0.8 ? sleep(1) : sleep((7 + rand() % (10 + 1 - 7)));

	numFiles = numFiles + 1; //increment # of files done

	//diagnostic message
	printf("\nThread got the string: %s\n", str);
	
	free(str);
	return NULL;
}

void sigUsrHandler(int signNum) { 
	//terminates when control c recieved
	if (signNum == SIGINT){
		printf("\n\nControl-c registered.\n");
		printf("Number of file requests recieved/serviced: %d\n", numFiles);
		printf("Exiting...\n\n");
		exit(0);
	}
}
