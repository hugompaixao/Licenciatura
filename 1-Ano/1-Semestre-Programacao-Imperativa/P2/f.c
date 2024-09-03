#include <stdio.h>
#include <math.h>

double sum_powers_from(double x,  double y, int n)
	{
		return n == 0 ?0 : pow(x+n-1, y) + sum_powers_from(x, y, n-1);
	}

void test()
	{
		double x;
		double y;
		int n;
		while (scanf("%lf%lf%d", &x, &y, &n) != EOF)
		{
			double result;
			result = (sum_powers_from (x , y, n));
			printf("%f\n", result);
		}
	}

int main()
	{
		test();
		return 0;
	}