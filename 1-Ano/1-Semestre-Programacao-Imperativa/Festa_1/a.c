#include<stdio.h> 
#include<math.h>
double price(int k) {
double p = (k * 0.087);
double r = ceil(p*2)/2;
return r;
}

double two_trips(int k) {
double p = ((price(k) * 2) * 0.85);
double r = ceil(p*2)/2;
return r;
}

void test() {
int k; 
while((scanf("%d",&k)) !=EOF) {
	double result1 = price(k);
	double result2 = two_trips(k);
	printf("%.2f %.2f\n", result1, result2);
	}
}

int main() {
test();
return 0;
}