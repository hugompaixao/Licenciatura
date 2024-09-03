#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

pthread_t thread, thread2;

char character;

sem_t semaphore, semaphore2;

void *printChar() {

	while(1) {

		sem_wait(&semaphore2);
		
		printf("%c", character);

		sem_post(&semaphore);
	}
}

void *input() {
	while(1) {
		sem_wait(&semaphore);
		scanf("%c", &character);

		if(character == 'X') {
			pthread_cancel(thread);
			pthread_cancel(thread2);
		}
		sem_post(&semaphore2);
	}
}

int main() {

	sem_init(&semaphore, 0, 1);
	sem_init(&semaphore2, 0, 0);

	pthread_create(&thread, NULL, input, NULL);
	
	pthread_create(&thread2, NULL, printChar, NULL);
	
	pthread_join(thread, NULL);
	pthread_join(thread2, NULL);

	sem_destroy(&semaphore);
	sem_destroy(&semaphore2);

	return 0;
}
