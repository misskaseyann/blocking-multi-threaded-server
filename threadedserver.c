#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/*
 * Lab Assignment 4
 * Blocking Multi-threaded Server
 *
 * @authors Kasey Stowell, Kehlsey Lewis
 * @version Fall 2018
 *
 */

void* fileget(void* arg);

int main() {
	// testing with just one thread to start with
	pthread_t thread1;
	void *result1;
	int status;
	char input[256];
	char* inputstr = input;
	
	// infinite loop?
	while(1) {
		// get user information
		printf("\nEnter File Name: ");
		scanf("%s", inputstr);
		// add error check for empty string?
		// create thread
		if ((status = pthread_create(&thread1, NULL, fileget, (void*)inputstr)) != 0) {
			fprintf(stderr, "thread create error %d: %s\n", status, strerror(status));
			exit(1);
		}
		// join with thread
		if ((status = pthread_join(thread1, &result1)) != 0) {
			fprintf(stderr, "join error %d: %s\n", status,strerror(status));
			exit(1);
		}
	}

}

void* fileget(void* arg) {
	char* str = (char*) arg;
	printf("\nThread got the string: %s\n", str);
	return NULL;
}
