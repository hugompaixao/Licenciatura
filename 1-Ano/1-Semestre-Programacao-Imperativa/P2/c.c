#include<stdio.h>
int sum_progression(int x0,int r,int n)
	{

		return((n*(2*x0+(n-1)*r))/2); 
	}

void result()
	{
		int x0;
		int r;
		int n;
		while(scanf("%d%d%d",&x0, &r, &n) !=EOF)
		{
			int z;
			z = sum_progression(x0,r,n);
			printf("%d\n", z);
		}
	} 
int main()
	{
		result();
		return 0;
	}