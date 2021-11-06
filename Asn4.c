
#include <pthread.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <stdio.h>
#include <time.h>
#include <math.h>

// max buffer size
#define BUFFER_SIZE 10000000

// all prime numbers under 100
int primes[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

// array of four thread pointers
pthread_t threads[4];

// buffers
int buffers[4][BUFFER_SIZE];

// buffer results
int results[4][BUFFER_SIZE];
int res_sizes[4] = {0, 0, 0, 0};// number of potential primes per buffer

// function producting a random int from 1 to 10^9
void get_rand(int* i) {
	srand(time(NULL) + rand());
	*i = (rand() % ((int)pow(10, 9))) + 1; 
}

// function that returns the index of the given thread reference in the threads[] array
int det_thread(pthread_t* id) {
	for (int i = 0; i < 4; i++) {
		if (id == &(threads[i])) {
			return i;
		}
	}
	return -1;
}

void *thread_function1(void *args) {
	int thread_num = det_thread((pthread_t*)args);
	for (int i = 0; i < BUFFER_SIZE; i++) {
				if (i < 3 && thread_num == 0) {
					printf("Please enter a number: ");
					scanf("%d", &(buffers[thread_num][i]));
				}
				else {
					get_rand(&(buffers[thread_num][i]));
				}
		}
    return NULL;
}

void *thread_function2(void *args) {
	int thread_num = det_thread((pthread_t*)args);
	int res_index = 0;
	for (int i = 0; i < BUFFER_SIZE; i++) {
		int possible = 1;
		for (int j = 0; j < 25; j++) {
			if ((buffers[thread_num][i] % primes[j]) == 0) {
				possible = 0;
				break;
			}
		}
		if (possible) {
			results[thread_num][res_index] = buffers[thread_num][i];
			res_index++;
		}
	}
	res_sizes[thread_num] = res_index;
    return NULL;
}

int main(void) {
	// create threads and execute thread_function1, passing each thread id to the function
	for (int i = 0; i < 4; i++) {
		pthread_create(&(threads[i]), NULL, thread_function1, (void*)&(threads[i]));
	}
	for (int i = 0; i < 4; i++) {// wait for all threads to be done
		pthread_join(threads[i], NULL);
	}

	// create threads and execute thread_function2, passing each thread id to the function
	for (int i = 0; i < 4; i++) {
		pthread_create(&threads[i], NULL, thread_function2, (void*)&(threads[i]));
	}
	for (int i = 0; i < 4; i++) {// wait for all threads to be done
		pthread_join(threads[i], NULL);
	}

	// calculating percentage of random numbers that turned out to be potential primes, should be around 12.031965%
	double percent = ((double)res_sizes[0] / pow(10, 9)) * 100;
	for (int i = 0; i < 4; i++) {
		double percent = ((double)res_sizes[i] / BUFFER_SIZE) * 100;
		printf("B%d: %f\n", i + 1, percent);
	}

	// number of results for each buffer
	printf("B1: %d, B2: %d, B3: %d, B4: %d\n", res_sizes[0], res_sizes[1], res_sizes[2], res_sizes[3]);

	// display the result from each thread in it's respective array
	for (int k = 0; k < 4; k++) {
		printf("\n\nBuffer %d Results: \n\n", k + 1);
		for (int i = 0; i < res_sizes[k]; i++) {
			printf("%d", results[k][i]);
			if (i < res_sizes[k] - 1) {
				printf(", ");
			}
		}
		printf("\n");
	}
	getchar();
	getchar();
	return 0;
}