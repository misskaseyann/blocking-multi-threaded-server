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
	char input[1024];
	
	// infinite loop?
	while(1) {
		printf("Enter File Name: ");
		scanf("\n%s", input);
		// echo debug
		printf("\n%s", input);
	}

}
