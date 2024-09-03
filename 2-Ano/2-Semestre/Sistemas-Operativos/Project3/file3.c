#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

pthread_mutex_t mutex;


void *work(void *id) {

	pthread_mutex_lock(&mutex);

	long num = (long) id;

	printf("Id: %ld.\n", num);

	sleep(rand() % 5);

	printf("Thread %ld awake.\n\n", num);

	pthread_mutex_unlock(&mutex);

	return NULL;
}

void createAndWait(int n) {
	pthread_t threads[n];

	pthread_mutex_init(&mutex, NULL);

	for(long i = 0; i < n; i++)
		pthread_create(&threads[i], NULL, work, (void *)i);

	for(int i = 0; i < n; i++)
		pthread_join(threads[i], NULL);

	pthread_mutex_destroy(&mutex);

}
   
int main() {
	int n;
	scanf("%d", &n);
	createAndWait(n);
	return 0;
}
