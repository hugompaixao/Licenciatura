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

int ints_max(const int *a, int n)
{
  assert(n > 0);
  int result = a[0];
  for (int i = 1; i < n; i++)  // i = 1
    if (result < a[i])
      result = a[i];
  return result;
}

int ints_min(const int *a, int n)
{
  assert(n > 0);
  int result = a[0];
  for (int i = 0; i < n; i++)
    if (result > a[i])
      result = a[i];
  return result;
}


int all_equal_or_not(int*a, int n){
	int result;
	if (ints_max(a,n) == ints_min(a,n))
		result = 1;
	else 
		result = 0;
	return result;
}

void all_equal_or_not_test()
{
	int a1[8] = {1,1,1,1,1,2,4,4,};
	assert (all_equal_or_not(a1, 8) == 0);
	assert (all_equal_or_not(a1, 7) == 0);
	assert (all_equal_or_not(a1, 6) == 0);
	assert (all_equal_or_not(a1, 5) == 1);
	
	int a2[6] = {4,4,4,1,8,5};     
	assert (all_equal_or_not(a2, 5) == 0);
	assert (all_equal_or_not(a2, 4) == 0);
	assert (all_equal_or_not(a2, 3) == 1);
	assert (all_equal_or_not(a2, 2) == 1);
}

void test(){
	int a[1000];
	int y = ints_get(a);
	int z = all_equal_or_not(a,y);
	printf("%d\n", z);
}

int main(){
	all_equal_or_not_test();
	test();
	return 0;
}
