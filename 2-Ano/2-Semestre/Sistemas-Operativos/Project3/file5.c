#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#ifndef NUM_THREADS
#define NUM_THREADS 10
#endif

#define NUM_MACHINE 2

pthread_t thread[NUM_THREADS];

sem_t full, empty;


void *machineUnUse(int client) {
    int machine = client % NUM_MACHINE;
    sem_wait(&full);
    printf("Cliente  %d terminou o uso da maquina %d\n.", client, machine);
    sem_post(&empty);
}

void *machineUse(int client) {
    int machine = client % NUM_MACHINE;
    sem_wait(&empty);
    printf("Cliente %d ésta a usar maquina %d.\n", client, machine);
    sem_post(&full);
}

void *store(void *thread_id) {
    long id = (long) thread_id;
    
    machineUse(id);
    sleep(1);
    machineUnUse(id);
}

int main() {

    sem_init(&empty, 0, NUM_MACHINE);
    sem_init(&full, 0, 0);

    for(long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&thread[i], NULL, store, (void *)i+1);

        printf("Cliente %ld chegou.\n", i+1);
    }

    for(int i = 0; i < NUM_THREADS; i++)
        pthread_join(thread[i], NULL);

    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
