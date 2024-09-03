#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>

int main() {
	int px[2], py[2], pr[2];
	
	if(pipe(px) < 0)
		exit(1);
	
	if(pipe(py) < 0)
		exit(1);
		
	if(pipe(pr) < 0)
		exit(1);
		
	pid_t pid = fork();
	while(1) {
		if(pid == 0) {
			int arr[3];
			close(px[1]);
			read(px[0], arr, sizeof(arr));
			
			//close(py[0]);
			//read(py[0], y, sizeof(y));
			
			arr[2] = arr[0] + arr[1];
			
			close(pr[0]);
			write(pr[1], arr, sizeof(arr));
		
		
		} else {
			int x, y;
			scanf("%d%d", &x, &y);
			
			int arr[3] = {x, y};
			close(px[0]);
			write(px[1], arr, sizeof(arr));
			
		 	//close(py[0]);
			//write(py[1], y, sizeof(y));
			int out[3];
			close(pr[1]);
			read(pr[0], out, sizeof(out));
			
			printf("%d\n", out[2]);
			
		}
	}
	return 0;
}
