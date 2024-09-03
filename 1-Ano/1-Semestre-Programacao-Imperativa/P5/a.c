#include<stdio.h>
#include<math.h>
double first_imi(double i)
{
double t = i*0.00315;
return t;
}
double imi (double i, int f)
{
double p;
if(f==1)
p = first_imi(i) * 0.9;
else
if (f==2)
p = first_imi(i) * 0.85;
else p = first_imi(i) * 0.8;
return p;
}
int desconto(double i,int f)
{
double a = first_imi(i) - imi(i,f);
double b;
if (a>80)
b =  first_imi(i) - 80;
else 
b = imi(i,f);
return b;
}
void test()
{
double i;
int f;
while((scanf("%lf%d", &i, &f))!=EOF)
	{
	int result;
	result = desconto(i,f);
	printf("%d\n", result);
	}	
}
int main()
{
test();
return 0;	
}