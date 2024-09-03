#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>

int main() {
	pid_t pid = fork();
	if(pid) {
		sleep(1);
		for(int i = 0; i < 5; i++) 
			printf("Eu sou o pai, minha identificação ém %d.\n", getpid());
	} else {
		for(int j = 0; j < 3; j++)
			printf("Eu sou o filho, meu pai é %d.\n", getppid());
	}
	exit(0);
}
