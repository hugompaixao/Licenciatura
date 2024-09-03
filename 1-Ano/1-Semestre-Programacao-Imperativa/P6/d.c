#include<stdio.h>
#include<assert.h>

int ints_gets(int*a){
	int result = 0;
	int x;
	while(scanf("%d", &x)!=EOF){
	a[result++] = x;
	}
	return result;
}
// Maximo e minimo para mostrat que elementos sao diferentes;
int ints_max(int*a, int n){
	assert(n > 0);
	int result = a[0];
	for(int i = 0; i < n; i++){
		if (result < a[i])
			result = a[i];
	}
	return result;
}

int ints_min(int *a, int n){
  assert(n > 0);
  int result = a[0];
  for (int i = 0; i < n; i++)
    if (result > a[i])
      	result = a[i];
  return result;
}
//Provar que sao diferentes valores;
int all_equal(int*a, int n){
	int result;
	if(ints_max(a,n) == ints_min(a,n))
		result = 1;
	else 
		result = 0;
	return result;
}
// Remove o primeiro maximmo do array;
int ints_remove(int *a, int n, int x, int *b){
	int result = 0;
	for (int i = 0; i < n; i++)
   	if (a[i] != x)
		b[result++] = a[i];
  return result;
}

int second_max(int*a , int n){
	assert (n >= 2 && all_equal(a,n) == 0); 
	int y = ints_max(a,n); // primeiro maximo
	int b[n];
	int z = ints_remove (a,n,y,b); // segundo maximo 
	int result = ints_max(b,z);
	return result; 
}

void second_max_test(){
  int a1[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
  assert(second_max(a1, 20) == 18);
  assert(second_max(a1, 10) == 8);
  assert(second_max(a1, 5) == 3);
  int a2[10] = {0,1,2,3,4,5,6,7,8,9};
  assert(second_max(a2, 10) == 8);
  assert(second_max(a2, 6) == 4);
}

void test(){
	int a[1000];
	int y = ints_gets(a);
	int z = second_max(a,y);
	printf("%d\n", z);
}

int main(){
	second_max_test();
	test();
	return 0;
}