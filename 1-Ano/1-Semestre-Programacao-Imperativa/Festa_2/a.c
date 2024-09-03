#include<stdio.h>
#include<assert.h>
#include"our_ints.h"
#include"our_doubles.h"
/*
// A
double all_rain_loule(double *a, int size){
	double result = 0;
	for(int i = 0; i < size; i++){
		if ((i+2)%2 == 0)
			result += a[i];
	}
	return result;
}

double all_rain_algarve(double *a, int size){
	double result = 0;
	for(int i = 0; i < size; i++){
		if ((i+2)%2 != 0)
			result += a[i];
	}
	return result;
}

double rainier_day_loule(double *a, int size){
	double result = 0;
	for(int i = 0; i < size; i++){
		if((i+2)%2 == 0)
			result = doubles_max(a,size);
	}
	return result;
}

double rainier_day_algarve(double *a, int size){
	double result = 0;
	for(int i = 0; i < size; i++){
		if((i+2)%2 != 0)
			result = doubles_max(a,size);
	}
	return result;
}

double rain_days_loule(double *a, int size){
	double result = 0;
	for(int i = 0; i < size; i++){
		if((i+2)%2 == 0){
			if(a[i] != 0)
				result++;
		}
	}
	return result;
}

double rain_days_algarve(double *a, int size){
	double result = 0;
	for(int i = 0; i < size; i++){
		if((i+2)%2 != 0){
			if(a[i] != 0)
				result++;
		}
	}
	return result;
}

double consecutive_rain_days_loule(double *a, int size){
	double result = 0;
	for(int i = 0; i < size; i++){
		if ((i+2)%2 == 0){
			if();
				result++;
		}
	}
	return result;
}

double consecutive_rain_days_algarve(double *a, int size){
	double result = 0;
	for(int i = 0; i < size; i++){
		if ((i+2)%2 != 0){
			if();
				result++;
		}
	}
	return result;
}

void test_penico(){
	double a[1000];
	double size =doubles_get(a);
	double b = all_rain_loule(a,size);
	double c = all_rain_algarve(a,size);
	double d = rainier_day_loule(a,size);
	double e = rain_days_algarve(a,size);
	double f = rain_days_loule(a,size);
	double g = rain_days_algarve(a,size);
	double h = consecutive_rain_days_loule(a,size);
	double i = consecutive_rain_days_algarve(a,size);
	printf("%lf %lf\n", b, c);
	printf("%lf %lf\n", d, e);
	printf("%lf %lf\n", f, g);
	printf("%lf %lf\n", h, i);
}
*/

//B


int camera(int *a, int size, int x, int y){
	int result;
	for(int i = 0; i < size; i++){
		if((a[i]+x) >= y)
			result = 1;
		else 
			result = 0;
	}
	return result;
}

int yes_no(int *a, int size, int x, int y){
	int result;
	int z = camera(a,size,x,y);
	if(z == 1)
		result = printf("YES\n");
	else if(z == 0)
		result = printf("NO\n");
	return result;

}

void test_camera(){
	int x;
	scanf("%d", &x);
	int a[1000];
	int size = ints_get_until(-1,a);
	int y;
	while(scanf("%d", &y)!=EOF){
		yes_no(a,size,x,y);
	}
}


// MAIN
int main(int argc, char **argv){
	int x = 'A';
	if (argc > 1)
		x = *argv[1];
	if (x == 'A'){
	//	test_penico();
	}
	else if (x == 'B'){
		test_camera();
	}
	else if (x == 'C'){}
	else if ("All unit tests PASSED.\n") 

	return 0; 
}