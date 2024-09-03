#include<stdio.h>
#include<assert.h>
#include"our_ints.h"
//#include"our_doubles.h"
/*---A-----------------------------------------------------------------------------------------------------------------------------------------------------*/


int xmas_gift(int *a, int size, int x){
	int result = 0;
	for(int i = 0; i < size; i++){
		result += a[i]/x; 
	}
	return result;
}


void unit_test_xmas_gift(){
	int a[6] = {7,3,2,5,6,10};
	assert(xmas_gift(a,6,3) == 9);
}


void test_xmas_gift(){
	int a[1000];
	int x;
	scanf("%d", &x);
	int size = ints_get(a);
	int z = xmas_gift(a,size,x);
	printf("%d\n", z);
}


/*---B------------------------------------------------------------------------------------------------------------------------------------------------------*/




int count(const int *a, int size)
{
    int result = 0;
    for (int i = 0; i < size; i++)
    	if (a[i] >= 3)
    		result++;
    return result;
}

int hat_trick(int *a, int size, int x, int *b){
	int result = 0;
	for(int i = 0; i < size; i += x)
	{
		if (i / x <= size / x){
			int z = count(a + i, x);
			b[result++] = z;
		}
		else {
			int z = count(a + size - i, size - i);
			b[result++] = z;
		}
	}
	return result;
}


void unit_test_hat_trick(){
	//int a[23] = {1,2,3,3,0,1,3,1,2,0,0,1,3,1,3,3,0,0,3,1,0,3,0};
	//int b[6];
	//int m = hat_trick(a,23,4,b);
	//int c[6] = {2,1,0,3,1,1};
	//assert(ints_equal(b, m, c, 6));
}


void test_hat_trick(){
	int a[1000];
	int b[1000];
	int x;
	scanf("%d", &x);
	int size = ints_get(a);
	int m = hat_trick(a,size,x,b);
	ints_println_special(b,m);
	
}


/*---C-----------------------------------------------------------------------------------------------------------------------------------------------------*/


double oil(double *a, int size, double *b){
	int result = 0;
	for(int i = 1; i < size; i++){
		if(a[i-1] != a[i])
			 b[result++]; // day
	}
	if(b[i-1] > b[i])
		re
	return result;
}

void unit_test_oil(){
	int a[]
}
void test_oil(){
	double a[1000];
	double b[1000];
	int size = doubles_get(a);
	int z = oil(a,size,b);
	printf("%d\n", z);
}

/*---Main--------------------------------------------------------------------------------------------------------------------------------------------------*/
int main(int argc, char **argv){
	int x = 'A';
	if (argc > 1)
		x = *argv[1];
	if (x == 'A'){
		unit_test_xmas_gift();
		test_xmas_gift();
	}
	else if (x == 'B'){
		unit_test_hat_trick();
		test_hat_trick();
	}
	else if (x == 'C'){
		//unit_test_oil();
		//test_oil();
	}
	else if ("All unit tests PASSED.\n") 

	return 0; 
}