// Octavio Andrade 64614

#include <stdio.h>
#include <math.h>

int is_zero (int x)
{
	return x == 0;
}
int sum_progression(int x0, int r, int n)
{
	return is_zero(n) ? 0 : x0 + sum_progression(x0+r, r, n-1);
}

// x = comprimento, y = altura
int blue(int x, int y)
{
	return sum_progression(1, 4, round(y/2.0));
}

int vertical_blue(int x, int y)
{
	int result;
	{
		if ((y+1)%2==1)
			result = ((round((x-y)/2.0)) * y);

		else 
			result = (floor((x-y)/2.0) * y); 
	}
	return result;
	
}

int yellow(int x, int y)
{
	return ((x*y) - blue(x, y) - vertical_blue(x, y));
}

void test_colors(void)
{
	int x;
	int y;
	while(scanf("%d%d", &x, &y) != EOF)
	{
		int z = blue(x, y) + vertical_blue(x, y);
		int w = yellow(x, y);
		printf("%d %d\n", z, w);
	}
}

int main(void)
{
	test_colors();
	return 0;
}