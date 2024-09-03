#include <stdio.h>
#include <math.h>

double sum_inverses(double n)
	{
 		return n == 0 ?0 : pow(n, -1) + sum_inverses(n-1);
	}

void test()
	{
		double n;
		while (scanf("%lf", &n) != EOF)
		{
			double result;
			result = sum_inverses(n);
			printf("%f\n", result);
		}
	}

int main()
	{
		test();
		return 0;
	}