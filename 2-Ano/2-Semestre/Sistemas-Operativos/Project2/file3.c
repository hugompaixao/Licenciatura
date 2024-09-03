#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>

char *changeStr(char *str, char *tmp) {
	for(int i = 0; str[i] != '\0'; i++) {
		if(str[i] >= 'A' && str[i] <= 'Z') 
			tmp[i] = (char) tolower(str[i]);
		else if(str[i] >= 'a' && str[i] <= 'z') 
			tmp[i] = (char) toupper(str[i]);
		else 
			tmp[i] = str[i];
	}
	return tmp;
}

int main() {
	int p[2];
	int p2[2];
	if(pipe(p) < 0)
		exit(1);
	if(pipe(p2) < 0)
		exit(1);
	pid_t pid = fork();
	while(1) {
		if(pid == 0) {
			int str, str1;
			scanf("%d", str);
			scanf("%d", str1);
			int arr[] = {str, str1};
			close(p[0]);
			write(p[1], arr, sizeof(arr));
			close(p2[1]);
			read(p2[0], arr, sizeof(arr));
			int sum = arr[0] + arr[1];

		} else {
			int arr[12];
			int x;
			close(p[1]);
			read(p[0], arr, sizeof(arr));
			close(p2[0]);
			write(p2[1], x, sizeof(x));
		}
	}
	return 0;
}
