#include <stdio.h>
int quadrado(int n)
{
	return (n*(n+1)*(2*n+1))/6;
}

int main()
{
	int x;
	int y;
	scanf("%d%d",&x,&y);
	int z = quadrado(y)-quadrado(x)+(x*x);
	printf("%d\n", z);
	return 0; 
}