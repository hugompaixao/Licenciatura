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

int position_even_minus_odd(int*a, int x){
	int result = 0;
	for(int i = 0; i < x; i++){
		if (i % 2 == 0)
			result += a[i];
		else 
			result -= a[i];
	}
	return result;
}

void position_even_minus_odd_test()
{
	int a1[8] = {0,1,0,1,0,1,0,1};
	assert (position_even_minus_odd(a1, 8) == -4);
	assert (position_even_minus_odd(a1, 7) == -3);
	assert (position_even_minus_odd(a1, 6) == -3);
	assert (position_even_minus_odd(a1, 5) == -2);
	
	int a2[6] = {1,0,1,0,1,0};     
	assert (position_even_minus_odd(a2, 5) == 3);
	assert (position_even_minus_odd(a2, 4) == 2);
	assert (position_even_minus_odd(a2, 3) == 2);
	assert (position_even_minus_odd(a2, 2) == 1);
}

void test(){
	int a[1000];
	int y = ints_get(a);
	int z = position_even_minus_odd(a,y);
	printf("%d\n", z);
}

int main(){
	position_even_minus_odd_test();
	test();
	return 0;
}

