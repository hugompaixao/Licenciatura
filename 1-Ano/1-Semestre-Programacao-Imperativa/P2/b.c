#include <stdio.h>
int sum_positive_integers(int x)
	{
		return x==0 ?x : (1+x)*x/2;
	}
int sum_multiples(int r, int n)
	{
		return 0 +r*(sum_positive_integers(n-1));
	}
void test()
	{
		int r;
		int n;
		while (scanf("%d%d", &r, &n) != EOF)
		{
			int result;
			result = sum_multiples(r,n);
			printf("%d\n", result);
		}
	}

int main()
	{
		test();
		return 0;
	}

