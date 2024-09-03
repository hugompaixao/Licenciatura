#include <stdio.h>
#include <math.h>
double sum_squares_from (double x, double n)
	{
  		return n == 0 ?0 : pow(x+n-1, 2) + sum_squares_from(x, n-1);
	}

void test()
	{
		double x;
		double n;
		while (scanf("%lf%lf", &x, &n) != EOF)
		{
			double result; 
			result = (sum_squares_from (x , n));
			printf("%f\n", result);
		}
	}

int main()
	{
		test();
		return 0;
	}