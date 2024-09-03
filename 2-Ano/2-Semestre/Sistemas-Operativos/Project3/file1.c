#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t mutex;

char *message = {"Mensagem da thread nº "};


void *printMessage(void *value) {
	pthread_mutex_lock(&mutex);

	long num = (long) value;

	for(int i = 0; i < strlen(message); i++) {
		printf("%c", message[i]);
	}

	printf("%ld\n", num);

	pthread_mutex_unlock(&mutex);
	
	return NULL;
}


int main() {
	pthread_t thread[5];
	pthread_mutex_init(&mutex, NULL);

	for(long i = 0; i < 5; i++) 
		pthread_create(&thread[i], NULL, printMessage, (void *)i);

	for(long i = 0; i < 5; i++)
		pthread_join(thread[i], NULL);

	pthread_mutex_destroy(&mutex);

	return 0;
}
