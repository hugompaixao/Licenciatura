#include <stdio.h>
#include <assert.h>

void ints_println_basic(const int *a, int n){
 	if (n > 0){
   		printf("%d", a[0]);
    	for (int i = 1; i < n; i++)  // i = 1
    	printf(" %d", a[i]);
  	}
  	printf("\n");
}

int ints_get(int *a){
  	int result = 0;
  	int x;
  	while (scanf("%d", &x) != EOF)
    a[result++] = x;
	return result;
  }

int ints_max(const int *a, int n){
  	assert(n > 0);
  	int result = a[0];
  	for (int i = 1; i < n; i++){  // i = 1
   		if (result < a[i])
      		result = a[i]; 
     }
  	return result;
}

int position(const int *a, int n, int x, int* b){
	int result = 0;
	for (int i = 0; i < n; i++){
		if (a[i] == x)
			b[result++] = i;
	}
	return result;
}

int ints_indices(const int *a, int n, int x, int* b){
    int result = 0;
  	for (int i = 0; i < n; i++){
    if (a[i] == x)
     	b[result++] = i; 
 	}
  	return result;
}

int argsmax(const int *a, int n, int *b){   
    assert(n > 0);
    int arg_max = ints_max(a, n);
    return ints_indices(a, n, arg_max, b);
   
}

void argsmax_test(){
	int a1[10] = {1, 2, 3, 2, 1, 2, 3, 2, 1, 3};
  	int b[10];
  	int c1 = argsmax(a1, 10, b);
  	assert(c1 == 3 && b[0] == 2 && b[1] == 6 && b[2] == 9);
}

void test(){
	int a[1000];
	int y = ints_get(a);
	int b[y];
	int z = argsmax(a,y,b);
	ints_println_basic(b, z);
}

int main(){
	test();
	argsmax_test();
	return 0;
}
