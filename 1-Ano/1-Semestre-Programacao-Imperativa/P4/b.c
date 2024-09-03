// 1 palmo = 20.32 cm = a
// 1 pe = 30.48 cm = b
// 1 passo = 152.40 cm = c
// 1 toesa = 182.88 cm = d
// 1 covado = 60.96 cm = e
// 1 vara = 101.60 cm = f
// 1 braca = 203.20 cm = g
// 1 polegada = 2.54 cm = h

#include<stdio.h>
#include<math.h>
double palmo(double a)
	{
		return (0.2032 * a);
	}
double pe(double b)
	{
		return (0.3048 * b);
	}
double passo(double c)
	{
		return (1.5240 * c);
	}
double toesa(double d)
	{
		return (1.8288 * d);
	}
double covado(double e)
	{
		return (0.6096 * e);
	}
double vara(double f)
	{
		return (1.0160 * f);
	}
double braca(double g)
	{
		return (2.0320 * g);
	}
double polegada(double h)
	{
		return (0.0254 * h);
	}
double sum(double a, double b, double c, double d, double e, double f, double g, double h)	
	{		
		return palmo(a) + pe(b) + passo(c) + toesa(d) + covado(e) + vara(f) + braca(g) + polegada(h);
	}
void test ()
	{
		double a;
		double b;
		double c;
		double d;
		double e;
		double f;
		double g;
		double h;
		while (scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &e, &f, &g, &h) != EOF)
			{
				double result;
				result = sum(a,b,c,d,e,f,g,h);
				printf("%.4f\n", result);
			}

	}
int main()
	{
		test();
		return 0;
	}