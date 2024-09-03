#include <stdio.h>
int sum_positive_integers(int n)
	{
		return n==0 ? n: sum_positive_integers(n-1)+n;
}
void sum_positive_integer()
	{
		int n;
		while (scanf("%d", &n) != EOF)
	{
		int z = sum_positive_integers(n);
		printf("%d\n", z);
	}
}
int main()
	{
		sum_positive_integer();
		return 0;
}