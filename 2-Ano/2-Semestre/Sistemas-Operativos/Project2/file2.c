#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>

int main() {
	printf("Eu sou o pai grande %d.\n", getpid());
	pid_t pid = fork();
	if(pid > 0) {
		for(int i = 0; i < 2; i++) {
			if(fork() == 0) {
				printf("Eu sou o filho %d, meu pai é %d\n", getpid(),getppid());
				exit(0);
			}
		}
	} else {
		for(int i = 0; i < 2; i++) {
			if(fork() == 0) {
				printf("Eu sou o filho %d, meu pai é %d\n", getpid(),getppid());
				exit(0);
			}
		}
		printf("Eu sou o filho %d, meu pai é %d\n", getpid(),getppid());
	}
	while(wait(NULL) != -1);
	return 0;
}
