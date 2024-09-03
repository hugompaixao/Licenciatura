// 1 2 3 2, repetição de 4 em 4
//resto da divisão de 4 ==> a=b%4
// golo,saltos==1,1  2,3  3,6  4,8  5,9  6,11  7,14  8,16  9,17  10,19  11,22  12,24
// resto das divisões por 4, 1 =1 ,  2 =2 ,  3 =3 ,  4 =0 ,   1 2 3 0 1 2 3 0 1 2 3 0
//resto 0 == b*2,  1== (b*2)-1,  2== (b*2)-1,  3== b*2

#include<stdio.h>
#include<math.h>

int somersaults(int g )
	{
		int a = g%4;
		int flips;
		if (g==0)
			flips = 0;
		else 
			if ((a==0) || (a==3))
				flips = g * 2;
			else 
				if ((a==1) || (a==2))
				flips = (g * 2) - 1;
		return flips;

	}

void test()
	{
		int x;
		while(scanf("%d",&x) !=EOF)
		{
			int result;
			result = somersaults(x);
			printf("%d\n", result);
		}
	}

int main()
	{
		test();
		return 0;
	}