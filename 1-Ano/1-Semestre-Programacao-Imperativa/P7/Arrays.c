// Santo Isidoro, ajuda-me com estes arrays malucos.
#include<stdio.h>
#include<assert.h>

#include"our_ints.h"

/*-----------------------------------------------------------------------A---------------------------------------------------------------*/

int ints_greater_than(const int *a, int size, int x, int *b){

	int result = 0;
	for (int i = 0;i < size; i++){
		if (a[i] > x)
			b[result++] = a[i];
	}
	return result;
}


void unit_ints_greater_than_test(void){

	int a[16] = {6,7,1,8,9,35,3,5,6,7,3,9,6,15,61,1};
	int b[16];
	int m1 = ints_greater_than(a, 16, 9, b);
	int c1[3] = {35, 15, 61};
	assert(ints_equal(b, m1, c1, 3));
	int m2 = ints_greater_than(a, 8, 5, b);
	int c2[5] = {6, 7, 8, 9, 35};
	assert(ints_equal(b, m2, c2, 5));
}


void ints_test_greater_than(void){

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


/*-----------------------------------------------------------------------B---------------------------------------------------------------*/

int ints_less_than(const int *a, int size, int x, int *b){

	int result = 0;
	for (int i = 0;i < size; i++){
		if (a[i] < x)
			b[result++] = a[i];
	}
	return result;
}


void unit_test_ints_less_than(void){

	int a1[5] = {1,2,3,4,5};
	int b1[5];
	int m1 = ints_less_than(a1,5,2,b1);
	assert(m1 == 1 && b1[0] == 1);
}


void ints_test_less_than(){

	int a[1000];
	int b[1000];
	int x;
	int size = ints_get_until(-1, a);
	while(scanf("%d", &x) != EOF)
	{
		int m = ints_less_than(a, size, x, b);
		ints_println_special(b, m);
	}
}


/*-----------------------------------------------------------------------C---------------------------------------------------------------*/

//int sum_digits(){}


//int digits_sums(int *a, int size){}



/*-----------------------------------------------------------------------D---------------------------------------------------------------*/
/*
int ints_append(const int *a, int n, const int *b, int m, int *c){

}
*/
/*-----------------------------------------------------------------------E---------------------------------------------------------------*/
/*
int ints_take(){

}
*/
/*-----------------------------------------------------------------------F---------------------------------------------------------------*/
/*
int ints_drop(){

}
*/
/*-----------------------------------------------------------------------G---------------------------------------------------------------*/
/*
int ints_ascending(){

}
*/
/*-----------------------------------------------------------------------H---------------------------------------------------------------*/
/*
int ints_accumulate(){

}
*/
/*-----------------------------------------------------------------------I---------------------------------------------------------------*/
/*
int ints_unaccumulate(){

}
*/
/*-----------------------------------------------------------------------J---------------------------------------------------------------*/
/*
int ints_find_triple(){
	int result = 0;
	for (int i = 0; i < n-2; i++){

	}

}
*/





int main(int argc, char **argv){
	int x = 'A';
	if (argc > 1)
		x = *argv[1];
	if (x == 'A'){ 
		unit_ints_greater_than_test(); 
		ints_test_greater_than(); 
	}
	else if (x == 'B'){ 
	ints_test_less_than(); 
	unit_test_ints_less_than(); 
	}
	else if (x == 'C'){}
	else if (x == 'D'){}
	else if (x == 'E'){}
	else if (x == 'F'){}
	else if (x == 'G'){}
	else if (x == 'H'){}
	else if (x == 'I'){}
	else if (x == 'J'){}
	else if ("All unit tests PASSED.\n") 

	return 0; 
}