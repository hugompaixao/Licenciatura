#include<stdio.h>
#include<assert.h>

int ints_get(int*a){
	int result = 0;
	int x;
	while (scanf("%d", &x)!=EOF){
		a[result++] = x;
	}
	return result;
}

int even_minus_odd(int*a, int x){
	int result = 0;
	for(int i = 0; i < x; i++){
		if (a[i] % 2 == 0)
			result += a[i];
		else 
			result -= a[i];
	}
	return result;
}

void even_minus_odd_test()
{
	int a1[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	assert (even_minus_odd(a1, 20) == -10);
	assert (even_minus_odd(a1, 15) == 7);
	assert (even_minus_odd(a1, 10) == -5);
	assert (even_minus_odd(a1, 5) == 2);
	
	int a2[10] = {0,1,2,3,4,5,6,7,8,9};     
	assert (even_minus_odd(a2, 10) == -5);
	assert (even_minus_odd(a2, 8) == -4);
	assert (even_minus_odd(a2, 6) == -3);
	assert (even_minus_odd(a2, 4) == -2);
}

void test(){
	int a[1000];
	int y = ints_get(a);
	int z = even_minus_odd(a,y);
	printf("%d\n", z);
}

int main(){
	even_minus_odd_test();
	test();
	return 0;
}