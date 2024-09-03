#include<stdio.h>
#include<math.h>
double salary(double s)
	{
		return (s / 60);
	}
int first(int h, int m)
	{
		int t = ((h-18)*60) + m;
		int r;
		if ((h-18)<2)
			r = t;
			else
				if ((h-18)==2)
					r= (2*60);
				else 
					if ((h-18)>2)
					r = (2*60);
		return r;
	}

int extra(int h, int m)
	{
		int p = ((h-20)*60) + m;
		int q;
		if ((h-20)==0)
			q = m;
		else 
			if ((h-20)>0)
				q = p;
			else
				if ((h-20)<0)
					q = 0;
		return q; 
	}
void test()
	{
		double s;
		int h;
		int m;
		while((scanf("%lf%d%d",&s, &h ,&m)!= EOF))
			{
				double result;
				result =(((first(h,m)*salary(s)))+((extra(h,m))*(salary(s)*1.5)));
				printf("%.6f\n",result);
			}
	}
int main()
	{
		test();
		return 0;
	}