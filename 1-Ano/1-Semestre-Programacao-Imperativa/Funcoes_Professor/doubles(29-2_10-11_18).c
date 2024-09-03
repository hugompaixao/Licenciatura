// Ficheiro dado na semana de 29 de Outubro - 2 de Novembro 2018

#include <stdio.h>
#include <assert.h>

int doubles_get(double *a)
{
  int result = 0;
  double x;
  while (scanf("%lf", &x) != EOF)
    a[result++] = x;
  return result;
}

void doubles_println_basic(const double *a, int n)
{
  if (n > 0)
  {
    printf("%g", a[0]);
    for (int i = 1; i < n; i++)  // i = 1
      printf(" %g", a[i]);
  }
  printf("\n");
}

int doubles_fill(double x, int n, double *a)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    a[result++] = x;
  return result;
}

int doubles_count(const double *a, int n, int x)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    if (a[i] == x)
      result++;
  return result;
}

void unit_test_doubles_count(void)
{
  double a1[16] = {6,7,1,8, 9,3,3,5, 6,7,3,9, 6,1,1,1};
  assert(doubles_count(a1, 16, 1) == 4);
  assert(doubles_count(a1, 16, 9) == 2);
  assert(doubles_count(a1, 16, 2) == 0);
  assert(doubles_count(a1, 8, 1) == 1);
  assert(doubles_count(a1, 8, 2) == 0);
  assert(doubles_count(a1, 0, 6) == 0);
}

double doubles_sum(const double *a, int n)
{
  double result = 0;
  for (int i = 0; i < n; i++)
    result += a[i];
  return result;
}

void unit_test_doubles_sum(void)
{
  double a1[8] = {6,7,1,8, 9,3,3,5};
  assert(doubles_sum(a1, 8) == 42);
  assert(doubles_sum(a1, 4) == 22);
  assert(doubles_sum(a1, 2) == 13);
  assert(doubles_sum(a1, 1) == 6);
  assert(doubles_sum(a1, 0) == 0);
  double a2[10] = {1,5,9,13, 17,21,25,29, 33,37};
  assert(doubles_sum(a2, 10) == 190);
  assert(doubles_sum(a2, 5) == 45);
}

double doubles_mean(const double *a, int n)
{
  assert(n > 0);
  return doubles_sum(a, n) / n;
}

int doubles_remove(const double *a, int n, int x, double *b)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    if (a[i] != x)
      b[result++] = a[i];
  return result;
}

void unit_test_doubles_remove(void)
{
  double a[5] = {6,7,1,8,7};
  double b1[5];
  double m1 = doubles_remove(a, 5, 7, b1);
  assert(m1 == 3 && b1[0] == 6 && b1[1] == 1 && b1[2] == 8);
  double b2[5];
  double m2 = doubles_remove(a, 5, 6, b2);
  assert(m2 == 4 && b2[0] == 7 && b2[1] == 1 && b2[2] == 8 && b2[3] == 7);
  double b3[5];
  double m3 = doubles_remove(a, 5, 3, b3);
  assert(m3 == 5 && b3[0] == 6 && b3[1] == 7 && b3[2] == 1 && b3[3] == 8 && b3[4] == 7);
  double b4[5];
  double m4 = doubles_remove(a, 0, 7, b4);
  assert(m4 == 0);
 }


double doubles_max(const double *a, int n)
{
  assert(n > 0);
  double result = a[0];
  for (int i = 1; i < n; i++)  // i = 1
    if (result < a[i])
      result = a[i];
  return result;
}

void unit_test_doubles_max(void)
{
  double a1[16] = {6,7,3,8, 9,3,3,5, 6,7,3,9, 6,1,8,3};
  assert(doubles_max(a1, 16) == 9);
  assert(doubles_max(a1, 4) == 8);
  assert(doubles_max(a1, 1) == 6);
  double a2[10] = {32,67,81,23, 27,12,90,13, 75,13};
  assert(doubles_max(a2, 10) == 90);
  assert(doubles_max(a2, 6) == 81);
  double a3[5] = {7e15,3e18,2e14,4e22,3e13};
  assert(doubles_max(a3, 5) == 4e22);
  double a4[5] = {7e-153,3e-185,2e-140,9e-225,3e-213};
  assert(doubles_max(a4, 5) == 2e-140);
  double a5[5] = {-7e200,-3e185,-2e240,-7e225,-3e280};
  assert(doubles_max(a5, 5) == -3e185);
}

double doubles_min(const double *a, int n)
{
  assert(n > 0);
  double result = a[0];
  for (int i = 0; i < n; i++)
    if (result > a[i])
      result = a[i];
  return result;
}

void unit_test_doubles_min(void)
{
  double a1[16] = {6,7,3,8, 9,3,3,5, 6,7,3,9, 6,1,8,3};
  assert(doubles_min(a1, 16) == 1);
  assert(doubles_min(a1, 4) == 3);
  assert(doubles_min(a1, 1) == 6);
  double a2[10] = {32,67,81,25, 27,42,90,13, 75,13};
  assert(doubles_min(a2, 10) == 13);
  assert(doubles_min(a2, 6) == 25);
}

int doubles_argmax(const double *a, int n)
{
  assert(n > 0);
  int result = 0;
  double m = a[0];
  for (int i = 1; i < n; i++)   // i = 1
    if (m < a[i])
      m = a[result = i];
  return result;
}

void unit_test_doubles_argmax(void)
{
  double a1[16] = {6,7,3,8, 9,3,3,5, 6,7,3,9, 6,1,8,3};
  assert(doubles_argmax(a1, 16) == 4);
  assert(doubles_argmax(a1, 4) == 3);
  assert(doubles_argmax(a1, 1) == 0);
  double a2[10] = {32,67,81,23, 27,12,90,13, 75,13};
  assert(doubles_argmax(a2, 10) == 6);
  assert(doubles_argmax(a2, 6) == 2);
}

int doubles_argmin(const double *a, int n)
{
  assert(n > 0);
  int result = 0;
  double m = a[0];
  for (int i = 1; i < n; i++)   // i = 1
    if (m > a[i])
      m = a[result = i];
  return result;
}

void unit_test_doubles_argmin(void)
{
  double a1[16] = {6,7,3,8, 9,3,3,5, 6,7,3,9, 6,1,8,3};
  assert(doubles_argmin(a1, 16) == 13);
  assert(doubles_argmin(a1, 4) == 2);
  assert(doubles_argmin(a1, 1) == 0);
  double a2[10] = {32,67,81,23, 27,12,90,13, 75,13};
  assert(doubles_argmin(a2, 10) == 5);
  assert(doubles_argmin(a2, 6) == 5);
}

int doubles_indices(const double *a, int n, double x, int* b)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    if (a[i] == x)
      b[result++] = i;
  return result;
}

void unit_test_doubles_indices(void)
{
  double a1[16] = {1,5,9,13, 5,5,7,3, 9,12,16,12, 1,1,12,5};
  int b11[16];
  int m11 = doubles_indices(a1, 16, 5.0, b11);
  assert(m11 == 4 && b11[0] == 1 && b11[1] == 4 && b11[2] == 5 && b11[3] == 15);
  int b12[16];
  int m12 = doubles_indices(a1, 16, 1.0, b12);
  assert(m12 == 3 && b12[0] == 0 && b12[1] == 12 && b12[2] == 13);
  int b13[16];
  int m13 = doubles_indices(a1, 16, 3.0, b13);
  assert(m13 == 1 && b13[0] == 7);
  int b14[16];
  int m14 = doubles_indices(a1, 16, 8.0, b14);
  assert(m14 == 0);
  int b15[16];
  int m15 = doubles_indices(a1, 0, 5.0, b15);
  assert(m15 == 0);

  double a2[5] = {4,4,4,4,4};
  int b21[5];
  int m21 = doubles_indices(a2, 6, 4.0, b21);
  assert(m21 == 5 && b21[0] == 0 && b21[1] == 1 && b21[2] == 2 && b21[3] == 3 && b21[4] == 4);
  int b22[5];
  int m22 = doubles_indices(a2, 6, 5.0, b22);
  assert(m22 == 0);
}

void unit_tests(void)
{
  unit_test_doubles_count();
  unit_test_doubles_sum();
  unit_test_doubles_remove();
  unit_test_doubles_indices();
  unit_test_doubles_max();
  unit_test_doubles_min();
  unit_test_doubles_argmax();
  unit_test_doubles_argmin();
}

int main(void)
{
  unit_tests();
  return 0;
}