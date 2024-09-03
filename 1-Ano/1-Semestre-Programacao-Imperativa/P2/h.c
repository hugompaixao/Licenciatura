#include <stdio.h>
#include <math.h>

double sum_inverse_squares(double n)
	{
  		return n == 0 ?0 : pow(n,-2) + sum_inverse_squares(n-1);
	}

void test()
	{
		double n;
		while (scanf("%lf", &n) != EOF)
		{
			double result;
			result = sum_inverse_squares(n);
			printf("%f\n", result);
		}
	}

int main()
	{
		test();
		return 0;
	}