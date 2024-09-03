//// Ficheiro dado na semana de 29 Outubro - 2 de Novembro de 2018

#include <stdio.h>
#include <assert.h>

void ints_println_basic(const int *a, int n)
{
  if (n > 0)
  {
    printf("%d", a[0]);
    for (int i = 1; i < n; i++)  // i = 1
      printf(" %d", a[i]);
  }
  printf("\n");
}

int ints_get(int *a)
{
  int result = 0;
  int x;
  while (scanf("%d", &x) != EOF)
    a[result++] = x;
  return result;
}

int ints_fill(int x, int n, int *a)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    a[result++] = x;
  return result;
}

int ints_count(const int *a, int n, int x)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    if (a[i] == x)
      result++;
  return result;
}

void unit_test_ints_count(void)
{
  int a1[16] = {6,7,1,8, 9,3,3,5, 6,7,3,9, 6,1,1,1};
  assert(ints_count(a1, 16, 1) == 4);
  assert(ints_count(a1, 16, 9) == 2);
  assert(ints_count(a1, 16, 2) == 0);
  assert(ints_count(a1, 8, 1) == 1);
  assert(ints_count(a1, 8, 2) == 0);
  assert(ints_count(a1, 0, 6) == 0);
}

int ints_sum(const int *a, int n)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    result += a[i];
  return result;
}

void unit_test_ints_sum(void)
{
  int a1[8] = {6,7,1,8, 9,3,3,5};
  assert(ints_sum(a1, 8) == 42);
  assert(ints_sum(a1, 4) == 22);
  assert(ints_sum(a1, 2) == 13);
  assert(ints_sum(a1, 1) == 6);
  assert(ints_sum(a1, 0) == 0);
  int a2[10] = {1,5,9,13, 17,21,25,29, 33,37};
  assert(ints_sum(a2, 10) == 190);
  assert(ints_sum(a2, 5) == 45);
}

int ints_mean(const int *a, int n)
{
  assert(n > 0);
  return ints_sum(a, n) / n;
}

int ints_remove(const int *a, int n, int x, int *b)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    if (a[i] != x)
      b[result++] = a[i];
  return result;
}

void unit_test_ints_remove(void)
{
  int a[5] = {6,7,1,8,7};
  int b1[5];
  int m1 = ints_remove(a, 5, 7, b1);
  assert(m1 == 3 && b1[0] == 6 && b1[1] == 1 && b1[2] == 8);
  int b2[5];
  int m2 = ints_remove(a, 5, 6, b2);
  assert(m2 == 4 && b2[0] == 7 && b2[1] == 1 && b2[2] == 8 && b2[3] == 7);
  int b3[5];
  int m3 = ints_remove(a, 5, 3, b3);
  assert(m3 == 5 && b3[0] == 6 && b3[1] == 7 && b3[2] == 1 && b3[3] == 8 && b3[4] == 7);
  int b4[5];
  int m4 = ints_remove(a, 0, 7, b4);
  assert(m4 == 0);
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

void unit_test_ints_max(void)
{
  int a1[16] = {6,7,3,8, 9,3,3,5, 6,7,3,9, 6,1,8,3};
  assert(ints_max(a1, 16) == 9);
  assert(ints_max(a1, 4) == 8);
  assert(ints_max(a1, 1) == 6);
  int a2[10] = {32,67,81,23, 27,12,90,13, 75,13};
  assert(ints_max(a2, 10) == 90);
  assert(ints_max(a2, 6) == 81);
  int a3[5] = {715,318,914,422,313};
  assert(ints_max(a3, 5) == 914);
  int a4[5] = {-2,0,2,-9,3};
  assert(ints_max(a4, 5) == 3);
  int a5[5] = {-7,-3,-1,-7,-3};
  assert(ints_max(a5, 5) == -1);
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

void unit_test_ints_min(void)
{
  int a1[16] = {6,7,3,8, 9,3,3,5, 6,7,3,9, 6,1,8,3};
  assert(ints_min(a1, 16) == 1);
  assert(ints_min(a1, 4) == 3);
  assert(ints_min(a1, 1) == 6);
  int a2[10] = {32,67,81,25, 27,42,90,13, 75,13};
  assert(ints_min(a2, 10) == 13);
  assert(ints_min(a2, 6) == 25);
  int a3[5] = {715,318,914,422,313};
  assert(ints_min(a3, 5) == 313);
  int a4[5] = {-2,0,2,-9,3};
  assert(ints_min(a4, 5) == -9);
  int a5[5] = {-7,-3,-0,-7,13};
  assert(ints_min(a5, 5) == -7);
}

int ints_argmax(const int *a, int n)
{
  assert(n > 0);
  int result = 0;
  int m = a[0];
  for (int i = 1; i < n; i++)   // i = 1
    if (m < a[i])
      m = a[result = i];
  return result;
}

void unit_test_ints_argmax(void)
{
  int a1[16] = {6,7,3,8, 9,3,3,5, 6,7,3,9, 6,1,8,3};
  assert(ints_argmax(a1, 16) == 4);
  assert(ints_argmax(a1, 4) == 3);
  assert(ints_argmax(a1, 1) == 0);
  int a2[10] = {32,67,81,23, 27,12,90,13, 75,13};
  assert(ints_argmax(a2, 10) == 6);
  assert(ints_argmax(a2, 6) == 2);
}

int ints_argmin(const int *a, int n)
{
  assert(n > 0);
  int result = 0;
  int m = a[0];
  for (int i = 1; i < n; i++)   // i = 1
    if (m > a[i])
      m = a[result = i];
  return result;
}

void unit_test_ints_argmin(void)
{
  int a1[16] = {6,7,3,8, 9,3,3,5, 6,7,3,9, 6,1,8,3};
  assert(ints_argmin(a1, 16) == 13);
  assert(ints_argmin(a1, 4) == 2);
  assert(ints_argmin(a1, 1) == 0);
  int a2[10] = {32,67,81,23, 27,12,90,13, 75,13};
  assert(ints_argmin(a2, 10) == 5);
  assert(ints_argmin(a2, 6) == 5);
}

int ints_indices(const int *a, int n, int x, int* b)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    if (a[i] == x)
      b[result++] = i;
  return result;
}

void unit_test_ints_indices(void)
{
  int a1[16] = {1,5,9,13, 5,5,7,3, 9,12,16,12, 1,1,12,5};
  int b11[16];
  int m11 = ints_indices(a1, 16, 5.0, b11);
  assert(m11 == 4 && b11[0] == 1 && b11[1] == 4 && b11[2] == 5 && b11[3] == 15);
  int b12[16];
  int m12 = ints_indices(a1, 16, 1.0, b12);
  assert(m12 == 3 && b12[0] == 0 && b12[1] == 12 && b12[2] == 13);
  int b13[16];
  int m13 = ints_indices(a1, 16, 3.0, b13);
  assert(m13 == 1 && b13[0] == 7);
  int b14[16];
  int m14 = ints_indices(a1, 16, 8.0, b14);
  assert(m14 == 0);
  int b15[16];
  int m15 = ints_indices(a1, 0, 5.0, b15);
  assert(m15 == 0);

  int a2[5] = {4,4,4,4,4};
  int b21[5];
  int m21 = ints_indices(a2, 6, 4.0, b21);
  assert(m21 == 5 && b21[0] == 0 && b21[1] == 1 && b21[2] == 2 && b21[3] == 3 && b21[4] == 4);
  int b22[5];
  int m22 = ints_indices(a2, 6, 5.0, b22);
  assert(m22 == 0);
}

void unit_tests(void)
{
  unit_test_ints_count();
  unit_test_ints_sum();
  unit_test_ints_remove();
  unit_test_ints_max();
  unit_test_ints_min();
  unit_test_ints_argmax();
  unit_test_ints_argmin();
  unit_test_ints_indices();
}

int main(void)
{
  unit_tests();
  return 0;
}
