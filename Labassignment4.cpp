/*
Created by Andrew Hingst (5043535).
A program that takes in 2 arguments at launch via command prompts as per argument:
./LabAss4 <Number of Threads> <Range to search>
and searches through the range to find all primes with the number of threads
requested. It proceeds to output them (in an albeit messy form).
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

//shared data by all thread(s)
int numThreads;
int range;
void *runner(void *param); //threads call this function

int main(int argc, char *argv[]) {
	pthread_t tid[10]; //thread identifier
	pthread_attr_t attr; //set of thread attributes

	if (argc !=3) {							//check for valid arguments
		fprintf(stderr, "usage: %s <integer value> <integer value>\n", argv[0]);
		return -1;
	}
	if (atoi(argv[1]) < 0) {
		fprintf(stderr, "%d must be >= 0\n", atoi(argv[1]));
		return -1;
	}
	
	numThreads = atoi(argv[1]);
	range = (atoi(argv[2]))/numThreads;
	//create thread

	for(int i = 0; i < numThreads; i++){		//create all threads, feed i as a parameter
		pthread_create(&tid[i],NULL,runner,(void*)i);
		
	}
	//wait for threads to exit
	for(int i = 0; i < numThreads; i++){
		pthread_join(tid[i],NULL);
}}

//The thread will begin control in this function
void *runner(void *param) {
	int i;//, maxVal = atoi((char*)param);
	int threadNum = (int)param;
	bool notPrime = false;

	for (i=(threadNum * range) + 1; i <= ((threadNum + 1 )* range); i++){ //Search the range for numbers
		for (int j = 2; j <= i/2; j++){							//Check to see if it has factors, mark if yes.
			if (i%j == 0) {
				notPrime = true;
			}
		}
		if (notPrime != true) {
			cout << "Thread " << threadNum << " found prime number : " << i << endl;	//no factors = output
		}
		notPrime = false;				//reset for next loop
	}
	pthread_exit(0);
}
