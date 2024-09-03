#include<stdio.h>
#include<math.h>
double nba(int a, int b)
	{
		return (a*30.48)+(b*2.54);
	}
 double meters(int a, int b)
 	{
 		return round(nba(a,b))/100;
 	}
void test()
	{
		int a;
		int b;
		while (scanf("%d%d", &a,&b) !=EOF)
			{
				double result;
				result = meters(a,b);
				printf("%.6f\n", result);
			}
	}
int main()
	{
		test();
		return 0;
	} 