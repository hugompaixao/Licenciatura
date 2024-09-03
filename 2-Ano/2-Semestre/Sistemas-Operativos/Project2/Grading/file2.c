#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	pid_t p0, p1, p2;
	
	p0 = fork();
	
	if(p0 == 0) {
		printf("Filho %d Pai %d\n", getpid(), getppid());
	} else {
		printf("Pai %d shell %d\n", getpid(), getppid());
		wait(NULL);
		
		p1 = fork();
		if(p1 == 0) {
			wait(NULL);
			printf("Filho %d Pai %d\n", getpid(), getppid());
		} else {
			p2 = fork();
			if(p2 == 0) {
				wait(NULL);
				printf("Filho %d Pai %d\n", getpid(), getppid());
			}
		}
	}
	
	
  return 0;
}
