#include <stdio.h>

int main(void)
{
	int x;
	int y = 2147483647;
	scanf("%d", &x);
	int z = y / x;
	printf("%d\n", z);
	return 0;
}

