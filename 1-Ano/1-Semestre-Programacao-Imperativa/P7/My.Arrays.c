// Santo Isidoro, ajuda-me com estes arrays malucos.
#include<stdio.h>
#include<assert.h>

#include"our_ints.h"


int ints_greater_than(const int *a, int n, int x, int *b)
{
	int result = 0;
	for (int i = 0;i < n; i++)
		if (a[i] > x)
			b[result++] = a[i];
	return result;
}

void unit_test_ints_greater_than(void)
{
	int a[16] = {6,7,1,8,9,35,3,5,6,7,3,9,6,15,61,1};
	int b[16];
	int m1 = ints_greater_than(a, 16, 9, b);
	int c1[3] = {35, 15, 61};
	assert(ints_equal(b, m1, c1, 3));
	int m2 = ints_greater_than(a, 8, 5, b);
	int c2[5] = {6, 7, 8, 9, 35};
	assert(ints_equal(b, m2, c2, 5));
	int m3 = ints_greater_than(a, 4, 6, b);
	int c3[2] = {7, 8};
	assert(ints_equal(b, m3, c3, 2));
	int m4 = ints_greater_than(a, 0, 1, b);
	int c4[0];
	assert(ints_equal(b, m4, c4, 0));
}

void test_ints_greater_than(void)
{
	int a[1000];
	int b[1000];
	int x;
	int n = ints_get_until(-1, a);
	while(scanf("%d", &x) != EOF)
	{
		int m = ints_greater_than(a, n, x, b);
		ints_println_special(b, m);
	}
}




int ints_less_than(const int *a, int n, int x, int *b)
{
	int result = 0;
	for (int i = 0;i < n; i++)
		if (a[i] < x)
			b[result++] = a[i];
	return result;
}

void unit_test_ints_less_than(void)
{
	int a1[5] = {1,2,3,4,5};
	int b1[5];
	int m1 = ints_less_than(a1,5,2,b1);
	assert(m1 == 1 && b1[0] == 1);
	int a2[10] = {1,2,3,4,5,6,7,8,9,10};
	int b2[10];
	int m2 = ints_less_than(a2,10,5,b2);
	assert(m2 == 4 && b2[0] == 1 && b2[1] ==2 && b2[2] == 3 && b2[3] == 4);
}

void test_ints_less_than(void)
{
	int a[1000];
	int b[1000];
	int x;
	int n = ints_get_until(-1, a);
	while(scanf("%d", &x) != EOF)
	{
		int m = ints_less_than(a, n, x, b);
		ints_println_special(b, m);
	}
}
int main(int argc, char **argv){
	int x = 'A';
	if (argc > 1)
		x = *argv[1];
	if (x == 'A'){ 
		unit_test_ints_greater_than(); 
		test_ints_greater_than(); 
	}
	else if (x == 'B'){ 
	test_ints_less_than(); 
	unit_test_ints_less_than(); 
	}
	else if ("All unit tests PASSED.\n") 

	return 0; 
}