#include <stdio.h>
int c(int n)
{
	return (n*(n+1)*(2*n+1))/6;
}

int main()
{
	int a;
	int b;
	scanf("%d%d",&a,&b);
	int final=c(b)-c(a)+(a*a);
	if(final<0)
		final=c(a)-c(b)+(b*b);
	printf("%d\n",final);
	return 0; 
}