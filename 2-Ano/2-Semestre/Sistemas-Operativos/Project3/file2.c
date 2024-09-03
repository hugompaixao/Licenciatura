#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *work(void *id) {
	long num = (long) id;

	printf("Id: %ld.\n", num);

	sleep(rand() % 1000);

	printf("Thread %ld awake.\n\n", num);

	return NULL;
}

int main() {
	pthread_t thread;

	long num = 1;

	pthread_create(&thread, NULL, work, (void *)num);

	pthread_join(thread, NULL);

	return 0;
}
