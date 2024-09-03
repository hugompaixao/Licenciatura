#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 2
#define NUM_LINES 4
#define NUM_COLUMNS 4

pthread_t threads[NUM_THREADS];

sem_t mutex;

int matrix_a[NUM_LINES][NUM_COLUMNS] = {{1, 1, 1, 1}, 
                                        {1, 1, 1, 1}, 
                                        {1, 1, 1, 1}, 
                                        {1, 1, 1, 1}};

int matrix_b[NUM_LINES][NUM_COLUMNS] = {{1, 2, 3, 4}, 
                                        {5, 6, 7, 8}, 
                                        {9, 10, 11, 12}, 
                                        {13, 14, 15, 16}};

int result[NUM_LINES][NUM_COLUMNS];

void *matrix_solve(void *arg) {
    sem_wait(&mutex);
    long idx = (long) arg;
    for(int i = 0; i < NUM_LINES; i++) {
        if(idx == i % NUM_THREADS)
            for(int j = 0; j < NUM_COLUMNS; j++) {
                result[i][j] = 0;
                for(int k = 0; k < NUM_COLUMNS; k++)
                    result[i][j] += matrix_a[i][k] * matrix_b[k][j];
        }
    }
    sem_post(&mutex);
}

int main() {

    sem_init(&mutex, 0, 1);

    for(long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, matrix_solve, (void *)i);
    }

    for(long i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    for(int i = 0; i < NUM_LINES; i++) {
        for(int  j = 0; j < NUM_COLUMNS; j++)
            printf("%d  ", result[i][j]);
        printf("\n");
    }

    sem_destroy(&mutex);
    return 0;
	
}
