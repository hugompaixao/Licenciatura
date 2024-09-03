#include<stdio.h>
#include<assert.h>
#include"our_ints.h"
#include"our_doubles.h"

/*---A-----------------------------------------------------------------------------------------------------------------------------------------------------*/


int positive_values(int *a, int size){
	
	int result = 0;
	while(result < size && a[result] >= 0)
	result++;
	return result;
}


int negative_values(int *a, int size){
	
	int result = 0;
	while(result < size && a[result] <= 0)
	result++;
	return result;
}


int penalty(int *a, int size, int *b){

	int result = 0;
	int i = 0;
	while(i < size){

	if(a[i] >= 0){ 
		int z = positive_values(a+i,size-i);
		b[result++] = z;
		i += z; 
	}

		else if(a[i] <= 0){ 
			int z =negative_values(a+i,size-i);
			b[result++] = z;
			i += z; 
		}
	}
	return result;
}


void unit_test_penalty(){
/*
		int a[21] = {4,6,8,3,-1,10,4,5,-3,-4,-3,7,0,0,-2,6,4,-4,-3,-2};
		int b[21];
		int c = penalty(a,21,b);
		assert(c == 21 && b[0] == 4 && b[1] == 1 && b[2] == 3 && b[3] == 3 && b[4]== 3 && b[5] == 1 && b[6] == 2 && b[7] == 3);
*/
}


void test_penalty(){

	int a[1000];
	int b[1000];
	int size_a = ints_get(a);
	int size_b = penalty(a, size_a, b);
	ints_println_special(b,size_b);

}


/*---B-----------------------------------------------------------------------------------------------------------------------------------------------------*/


int ascendente(int *a, int size){

	int x = 0;
	int idx = a[0];
	int result = 0;
	for(int i = 1; i < size; i++){
		if(idx < a[i]){
			if(x == 0) result = 1;
			idx = a[i];
		}
		else{
			idx = a[i];
			x = 1; 
		}
	}
	return result;
}


int descendente(int *a, int size){
	int x = 0;
	int idx = a[0];
	int result = 0;
	for(int i = 1; i < size; i++){
		if(idx > a[i]){
			if( x == 1) result = 1;
			idx = a[i];
		}
		else{
			idx = a[i];
			x = 1;
		}
	}
	return result;
}


int bitonico(int *b, int size){

	int result;
	int idx1 = b[0];
	int idx2 = b[1];
	int asc = 0;
	int desc = 0;
	if(idx1 > idx2)
		desc = descendente(b,size);
	else
		asc = ascendente(b,size);
	if(asc == 0 && desc == 0)
		result = printf("bitonico");
	else 
		printf("desordenado");
	return result;
}


void unit_test_bitonico(){
	/*	int a[7] = {2,5,8,14,10,8,2};
		int x;
		int c = bitonico(a,7);
		assert(x == bitonico);

		int a[4] = {7,9,1,6};
		int c = bitonico(a,4);
		assert(x == desordenado);
*/}

	
void test_bitonico(){
	int a[1000];
	int b[1000];
	int x = ints_get(a);
	bitonico(b,x);
}


/*---C-----------------------------------------------------------------------------------------------------------------------------------------------------*/


int double_count(double *a, int size, int x){
	int result = 0;
	for(int i = 0; i < size; i++){
		if(a[i] <= x)
			result++;
	}
	return result;
}


int december(double *a, int size, int *b){
	assert(size <= 3100 && size%31 == 0);
	int result = 0;
	for(int i = 0; i < size/31; i++){
		if(double_count(a+(i+31),31,0) >= 3)
			b[result++] = i;
	}
	return result;
}


int decembre_1(int *b, int size, int m){
	return size/31 - b[m-1];
}


void test_december(){
	double a[3100];
	int size = doubles_get(a);
	int b[100];
	int y = december(a,size,b);
	printf("%d\n", y);
	if(y > 0){
		int z = decembre_1(b,size,y);
		printf("%d\n", z);
	}
	else 
		printf("\n");
}


/*---Main--------------------------------------------------------------------------------------------------------------------------------------------------*/


int main(int argc, char **argv){
	int x = 'A';
	if (argc > 1)
		x = *argv[1];
	if (x == 'A'){
		unit_test_penalty();
		test_penalty();
	}
	else if (x == 'B'){
		unit_test_bitonico();
		test_bitonico();
	}
	else if (x == 'C'){
		test_december();
	}
	else if ("All unit tests PASSED.\n") 

	return 0; 
}
