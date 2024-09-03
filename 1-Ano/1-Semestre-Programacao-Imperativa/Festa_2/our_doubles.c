//
//  our_doubles.c
//
//  Created by Pedro Guerreiro on 01/11/2018.
//  Copyright © 2018 Pedro Guerreiro. All rights reserved.
//

#include <stdio.h>
#include <assert.h>

#include "our_ints.h"
#include "our_doubles.h"

// Write array elements in a line, separated by a space.
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

// Like doubles_println_basic, but empty arrays are represented
// by a line with an asterisk.
void doubles_println_special(const double *a, int n)
{
  if (n == 0)
    printf("*\n");
  else
    doubles_println_basic(a, n);
}

// Read array elements until no more items exists for reading.
int doubles_get(double *a)
{
  int result = 0;
  double x;
  while (scanf("%lf", &x) != EOF)
    a[result++] = x;
  return result;
}

// Read array elements until a terminator value is read
// or until no more items exist for reading.
// The terminator is NOT read into the array.
int doubles_get_until(double terminator, double *a)
{
  int result = 0;
  double x;
  while (scanf("%lf", &x) != EOF && x != terminator)
    a[result++] = x;
  return result;
}

// Read at most `n` array elements
// or until no more items exist for reading, whichever happens first.
int doubles_get_some(double *a, int n)
{
  int result = 0;
  double x;
  while (result < n && scanf("%lf", &x) != EOF)
    a[result++] = x;
  return result;
}

// Read two arrays in parallel, until EOF.
int doubles_get_two(double *a, double *b)
{
  int result = 0;
  double x, y;
  while (scanf("%lf%lf", &x, &y) != EOF)
  {
    a[result] = x;
    b[result] = y;
    result++;
  }
  return result;
}

// The first `n` elements of `a` will have value `x`.
int doubles_fill(double x, int n, double *a)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    a[result++] = x;
  assert(result == n);
  return result;
}

// How many elements of `a` have value `x`?
int doubles_count(const double *a, int n, double x)
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
  assert(doubles_count(a1, 16, 1.0) == 4);
  assert(doubles_count(a1, 16, 9.0) == 2);
  assert(doubles_count(a1, 16, 2.0) == 0);
  assert(doubles_count(a1, 8, 1.0) == 1);
  assert(doubles_count(a1, 8, 2.0) == 0);
  assert(doubles_count(a1, 0, 6.0) == 0);
}

// Sum of all elements of the array.
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
  assert(doubles_sum(a1, 8) == 42.0);
  assert(doubles_sum(a1, 4) == 22.0);
  assert(doubles_sum(a1, 2) == 13.0);
  assert(doubles_sum(a1, 1) == 6.0);
  assert(doubles_sum(a1, 0) == 0.0);
  double a2[10] = {1,5,9,13, 17,21,25,29, 33,37};
  assert(doubles_sum(a2, 10) == 190.0);
  assert(doubles_sum(a2, 5) == 45.0);
}

// Average of the array
double doubles_mean(const double *a, int n)
{
  assert(n > 0);
  return doubles_sum(a, n) / n;
}

// Array `b` has all elements of `a`, except those with value `x`, in the
// same order.
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
  int m1 = doubles_remove(a, 5, 7.0, b1);
  double c1[3] = {6,1,8};
  assert(doubles_equal(b1, m1, c1, 3));
  double b2[5];
  int m2 = doubles_remove(a, 5, 6.0, b2);
  double c2[4] = {7,1,8,7};
  assert(doubles_equal(b2, m2, c2, 4));
  double b3[5];
  double m3 = doubles_remove(a, 5, 3.0, b3);
  assert(doubles_equal(b3, m3, a, 5));
  double b4[5];
  double m4 = doubles_remove(a, 0, 7.0, b4);
  assert(m4 == 0);
 }

// Max value of non-empty array.
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
  assert(doubles_max(a1, 16) == 9.0);
  assert(doubles_max(a1, 4) == 8.0);
  assert(doubles_max(a1, 1) == 6.0);
  double a2[10] = {32,67,81,23, 27,12,90,13, 75,13};
  assert(doubles_max(a2, 10) == 90.0);
  assert(doubles_max(a2, 6) == 81.0);
  double a3[5] = {715,318,914,422,313};
  assert(doubles_max(a3, 5) == 914.0);
  double a4[5] = {-2,0,2,-9,3};
  assert(doubles_max(a4, 5) == 3.0);
  double a5[5] = {-7,-3,-1,-7,-3};
  assert(doubles_max(a5, 5) == -1.0);
}

// Min value of non-empty array.
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
  assert(doubles_min(a1, 16) == 1.0);
  assert(doubles_min(a1, 4) == 3.0);
  assert(doubles_min(a1, 1) == 6.0);
  double a2[10] = {32,67,81,25, 27,42,90,13, 75,13};
  assert(doubles_min(a2, 10) == 13.0);
  assert(doubles_min(a2, 6) == 25.0);
  double a3[5] = {715,318,914,422,313};
  assert(doubles_min(a3, 5) == 313.0);
  double a4[5] = {-2,0,2,-9,3};
  assert(doubles_min(a4, 5) == -9.0);
  double a5[5] = {-7,-3,-0,-7,13};
  assert(doubles_min(a5, 5) == -7.0);
}

// Index of first ocurrence of the max value in the array.
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

// Index of first ocurrence of the min value in the array.
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

// Array of the positions of `x` in `a`.
int doubles_indices(const double *a, int n, int x, int* b)
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
  int m11 = doubles_indices(a1, 16, 5, b11);
  int c11[4] = {1,4,5,15};
  assert(ints_equal(b11, m11, c11, 4));
  int b12[16];
  int m12 = doubles_indices(a1, 16, 1, b12);
  int c12[4] = {0, 12, 13};
  assert(ints_equal(b12, m12, c12, 3));
  int b13[16];
  int m13 = doubles_indices(a1, 16, 3, b13);
  assert(m13 == 1 && b13[0] == 7);
  int b14[16];
  int m14 = doubles_indices(a1, 16, 8, b14);
  assert(m14 == 0);
  int b15[16];
  int m15 = doubles_indices(a1, 0, 5, b15);
  assert(m15 == 0);

  double a2[5] = {4,4,4,4,4};
  int b21[5];
  int m21 = doubles_indices(a2, 6, 4.0, b21);
  int c21[5] = {0,1,2,3,4};
  assert(ints_equal(b21, m21, c21, 5));
  int b22[5];
  int m22 = doubles_indices(a2, 6, 5.0, b22);
  assert(m22 == 0);
}

// Index of the first occurrence of `x` in `a` or -1 if it does not occur.
int doubles_find(const double *a, int n, double x)
{
  for (int i = 0; i < n; i++)
    if (a[i] == x)
      return i;
  return -1;
}

void unit_test_doubles_find(void)
{
  double a[] = {9,5,6,6, 5,7,5,3};
  assert(doubles_find(a, 8, 9.0) == 0);
  assert(doubles_find(a, 8, 5.0) == 1);
  assert(doubles_find(a, 8, 6.0) == 2);
  assert(doubles_find(a, 8, 7.0) == 5);
  assert(doubles_find(a, 8, 3.0) == 7);
  assert(doubles_find(a, 8, 2.0) == -1);
  assert(doubles_find(a, 4, 7.0) == -1);
  assert(doubles_find(a, 4, 5.0) == 1);
  assert(doubles_find(a, 0, 9.0) == -1);
  assert(doubles_find(a, 0, 4.0) == -1);
  double b[] = {3,3,3,3};
  assert(doubles_find(b, 4, 3.0) == 0);
  assert(doubles_find(b, 4, 5.0) == -1);
}

// Are the two arrays equal?
int doubles_equal(const double *a, int n, const double *b, int m)
{
  int result = n == m;
  int i = 0;
  while (result && i < n)
    if (a[i] != b[i])
      result = 0;
    else
      i++;
  return result;
}

void unit_test_doubles_equal(void)
{
  double a[] = {7, 4, 1, 5};
  double b[] = {7, 4, 2, 7, 5};
  double c[] = {4, 1, 5, 7};
  double d[] = {4, 1, 5, 8};
  assert(doubles_equal(a, 4, a, 4));
  assert(doubles_equal(a, 2, b, 2));
  assert(doubles_equal(c, 3, d, 3));
  assert(doubles_equal(a, 0, c, 0));
  assert(!doubles_equal(a, 3, c, 2));
  assert(!doubles_equal(a, 4, b, 5));
  assert(!doubles_equal(c, 4, d, 4));
  assert(!doubles_equal(a, 3, b, 3));
}

// Number of elements of `a` before first ocurrence of an element with value
// not equal to `x` or `n` if all elements are equal to `x`.
int doubles_count_while(const double *a, int n, double x)
{
  int result = 0;
  while (result < n && a[result] == x)
    result++;
  return result;
}

void unit_test_doubles_count_while(void)
{
  double a[16] = {4,4,4,3, 5,9,9,5, 5,5,5,5, 5,5,1,1};
  assert(doubles_count_while(a, 16, 4) == 3);
  assert(doubles_count_while(a, 16, 7) == 0);
  assert(doubles_count_while(a+4, 12, 5) == 1);
  assert(doubles_count_while(a+4, 12, 2) == 0);
  assert(doubles_count_while(a+8, 8, 5) == 6);
  assert(doubles_count_while(a+8, 8, 3) == 0);
  assert(doubles_count_while(a+14, 2, 1) == 2);
  assert(doubles_count_while(a+14, 2, 3) == 0);
}

// Number of elements of `a` before first ocurrence of an element with value
// equal to `x` or `n` if all elements not are equal to `x`.
int doubles_count_while_not(const double *a, int n, double x)
{
  int result = 0;
  while (result < n && a[result] != x)
    result++;
  return result;
}

void unit_test_doubles_count_while_not(void)
{
  double a[16] = {4,4,4,3, 5,9,9,5, 5,5,5,5, 5,5,1,5};
  assert(doubles_count_while_not(a, 16, 4) == 0);
  assert(doubles_count_while_not(a, 16, 5) == 4);
  assert(doubles_count_while_not(a+4, 12, 5) == 0);
  assert(doubles_count_while_not(a+4, 12, 1) == 10);
  assert(doubles_count_while_not(a+8, 8, 5) == 0);
  assert(doubles_count_while_not(a+8, 8, 1) == 6);
  assert(doubles_count_while_not(a+8, 8, 3) == 8);
}

// Array `b` contains the first element of each run of equal elements
// in the array `a`, in the same order.
int doubles_unique(const double *a, int n, double *b)
{
  int result = 0;
  int i = 0;
  while (i < n)
  {
    int z = doubles_count_while(a+i, n-i, a[i]);
    b[result++] = a[i];
    i += z;
  }
  return result;
}

void unit_test_doubles_unique(void)
{
  double a1[16] = {4,9,4,4, 4,7,7,7, 7,7,8,6, 6,6,6,4};
  double b1[16];
  double c1[7] = {4,9,4,7,8,6,4};
  int m1 = doubles_unique(a1, 16, b1);
  assert(doubles_equal(b1, m1, c1, 7));
  
  double a2[8] = {4,4,4,4, 4,4,4,4};
  double b2[8];
  double c2[1] = {4};
  int m2 = doubles_unique(a2, 8, b2);
  assert(doubles_equal(b2, m2, c2, 1));
}

// Array `b` contains the number of elements in each run of equal elements
// in the array `a`, in the same order.
int doubles_groups(const double *a, int n, int *b)
{
  int result = 0;
  int i = 0;
  while (i < n)
  {
    int z = doubles_count_while(a+i, n-i, a[i]);
    b[result++] = z;
    i += z;
  }
  return result;
}

void unit_test_doubles_groups(void)
{
  double a1[16] = {4,9,4,4, 4,7,7,7, 7,7,8,6, 6,6,6,4};
  int b1[16];
  int c1[7] = {1,1,3,5,1,4,1};
  int m1 = doubles_groups(a1, 16, b1);
  assert(ints_equal(b1, m1, c1, 7));
  
  double a2[8] = {4,4,4,4, 4,4,4,4};
  int b2[8];
  int c2[1] = {8};
  int m2 = doubles_groups(a2, 8, b2);
  assert(ints_equal(b2, m2, c2, 1));
}

// Array `b` shall containt the length of each run of elements with
// value `x` in array `a`.
int doubles_runs(const double *a, int n, double x, int *b)
{
  int result = 0;
  int i = 0;
  while (i < n)
    if (a[i] == x)
    {
      int z = doubles_count_while(a+i, n-i, x);
      b[result++] = z;
      i += z;
    }
    else
      i++;
  return result;
}

void unit_test_doubles_runs(void)
{
  double a1[24] = {4,9,4,4, 4,7,7,7, 7,7,8,6, 6,6,6,4, 7,4,4,6, 6,9,9,4};
  int b11[24];
  int m11 = doubles_runs(a1, 24, 4, b11);
  int c11[5] = {1, 3, 1, 2, 1};
  assert(ints_equal(b11, m11, c11, 5));
  int b12[24];
  int m12 = doubles_runs(a1, 24, 7, b12);
  int c12[2] = {5, 1};
  assert(ints_equal(b12, m12, c12, 2));
  int b13[24];
  int m13 = doubles_runs(a1, 24, 8, b13);
  int c13[1] = {1};
  assert(ints_equal(b13, m13, c13, 1));
  int b14[24];
  int m14 = doubles_runs(a1, 24, 5, b14);
  assert(m14 == 0);
  
  double a2[8] = {4,4,4,4, 4,4,4,4};
  int b21[8];
  int m21 = doubles_runs(a2, 8, 4, b21);
  int c21[1] = {8};
  assert(ints_equal(b21, m21, c21, 1));
  int b22[8];
  int m22 = doubles_runs(a2, 8, 5, b22);
  assert(m22 == 0);
}

// Array `b` shall contain the length of each run of elements with
// value not equal to `x` in array `a`.
int doubles_runs_not(const double *a, int n, double x, int *b)
{
  int result = 0;
  int i = 0;
  while (i < n)
    if (a[i] != x)
    {
      int z = doubles_count_while_not(a+i, n-i, x);
      b[result++] = z;
      i += z;
    }
    else
      i++;
  return result;
}

void unit_test_doubles_runs_not(void)
{
  double a1[24] = {4,9,4,4, 4,7,7,7, 7,7,8,6, 6,6,6,4, 7,4,4,6, 6,9,9,4};
  int b11[24];
  int m11 = doubles_runs_not(a1, 24, 4, b11);
  int c11[4] = {1, 10, 1, 4};
  assert(ints_equal(b11, m11, c11, 4));
  int b12[24];
  int m12 = doubles_runs_not(a1, 24, 7, b12);
  int c12[3] = {5, 6, 7};
  assert(ints_equal(b12, m12, c12, 3));
  int b13[24];
  int m13 = doubles_runs_not(a1, 24, 8, b13);
  int c13[2] = {10, 13};
  assert(ints_equal(b13, m13, c13, 2));
  int b14[24];
  int m14 = doubles_runs_not(a1, 24, 5, b14);
  int c14[1] = {24};
  assert(ints_equal(b14, m14, c14, 1));
  
  double a2[8] = {4,4,4,4, 4,4,4,4};
  int b21[8];
  int m21 = doubles_runs_not(a2, 8, 4, b21);
  assert(m21 == 0);
  int b22[8];
  int c22[1] = {8};
  int m22 = doubles_runs_not(a2, 8, 5, b22);
  assert(ints_equal(b22, m22, c22, 1));
}

// Array `b` shall contain the length of each run of `x` in array `a`,
// and array `c` shall contain the start position of each run.
int doubles_runs_starts(const double *a, int n, double x, int *b, int *c)
{
  int result = 0;
  int i = 0;
  while (i < n)
    if (a[i] == x)
    {
      int z = doubles_count_while(a+i, n-i, x);
      b[result] = z;
      c[result] = i;
      result++;
      i += z;
    }
    else
      i++;
  return result;
}

void unit_test_doubles_runs_starts(void)
{
  double a1[24] = {4,9,4,4, 4,7,7,7, 7,7,8,6, 6,6,6,4, 7,4,4,6, 6,9,9,4};
  int b11[24];
  int c11[24];
  int m11 = doubles_runs_starts(a1, 24, 4, b11, c11);
  int d11[7] = {1, 3, 1, 2, 1};
  int e11[7] = {0, 2, 15, 17, 23};
  assert(ints_equal(b11, m11, d11, 5));
  assert(ints_equal(c11, m11, e11, 5));
  int b12[24];
  int c12[24];
  int m12 = doubles_runs_starts(a1, 24, 7, b12, c12);
  int d12[2] = {5, 1};
  int e12[2] = {5, 16};
  assert(ints_equal(b12, m12, d12, 2));
  assert(ints_equal(c12, m12, e12, 2));
  int b13[24];
  int c13[24];
  int m13 = doubles_runs_starts(a1, 24, 8, b13, c13);
  int d13[1] = {1};
  int e13[1] = {10};
  assert(ints_equal(b13, m13, d13, 1));
  assert(ints_equal(c13, m13, e13, 1));
  int b14[24];
  int c14[24];
  int m14 = doubles_runs_starts(a1, 24, 5, b14, c14);
  assert(m14 == 0);
  
  double a2[8] = {4,4,4,4, 4,4,4,4};
  int b21[8];
  int c21[8];
  int m21 = doubles_runs_starts(a2, 8, 4, b21, c21);
  int d21[1] = {8};
  int e21[1] = {0};
  assert(ints_equal(b21, m21, d21, 1));
  assert(ints_equal(c21, m21, e21, 1));
  int b22[8];
  int c22[8];
  int m22 = doubles_runs_starts(a2, 8, 5, b22, c22);
  assert(m22 == 0);
}

// Array `b` shall containt the length of each run of values not equal to `x`
// in array `a`, and array `c` shall contain the start position of each run.
int doubles_runs_starts_not(const double *a, int n, double x, int *b, int *c)
{
  int result = 0;
  int i = 0;
  while (i < n)
    if (a[i] != x)
    {
      int z = doubles_count_while_not(a+i, n-i, x);
      b[result] = z;
      c[result] = i;
      result++;
      i += z;
    }
    else
      i++;
  return result;
}

void unit_test_doubles_runs_starts_not(void)
{
  double a1[24] = {4,9,4,4, 4,7,7,7, 7,7,8,6, 6,6,6,4, 7,4,4,6, 6,9,9,4};
  int b11[24];
  int c11[24];
  int m11 = doubles_runs_starts_not(a1, 24, 4, b11, c11);
  int d11[4] = {1, 10, 1, 4};
  int e11[4] = {1, 5, 16, 19};
  assert(ints_equal(b11, m11, d11, 4));
  assert(ints_equal(c11, m11, e11, 4));
  int b12[24];
  int c12[24];
  int m12 = doubles_runs_starts_not(a1, 24, 7, b12, c12);
  int d12[3] = {5, 6, 7};
  int e12[3] = {0, 10, 17};
  assert(ints_equal(b12, m12, d12, 3));
  assert(ints_equal(c12, m12, e12, 3));
  int b13[24];
  int c13[24];
  int m13 = doubles_runs_starts_not(a1, 24, 8, b13, c13);
  int d13[2] = {10, 13};
  int e13[2] = {0, 11};
  assert(ints_equal(b13, m13, d13, 2));
  assert(ints_equal(c13, m13, e13, 2));
  int b14[24];
  int c14[24];
  int m14 = doubles_runs_starts_not(a1, 24, 5, b14, c14);
  int d14[1] = {24};
  int e14[1] = {0};
  assert(ints_equal(b14, m14, d14, 1));
  assert(ints_equal(c14, m14, e14, 1));
  
  double a2[8] = {4,4,4,4, 4,4,4,4};
  int b21[8];
  int c21[8];
  int m21 = doubles_runs_starts_not(a2, 8, 4, b21, c21);
  assert(m21 == 0);
  int b22[8];
  int c22[8];
  int m22 = doubles_runs_starts_not(a2, 8, 5, b22, c22);
  int d22[1] = {8};
  int e22[1] = {0};
  assert(ints_equal(b22, m22, d22, 1));
  assert(ints_equal(c22, m22, e22, 1));
}

void doubles_unit_tests(void)
{
  unit_test_doubles_count();
  unit_test_doubles_sum();
  unit_test_doubles_remove();
  unit_test_doubles_max();
  unit_test_doubles_min();
  unit_test_doubles_argmax();
  unit_test_doubles_argmin();
  unit_test_doubles_indices();
  unit_test_doubles_find();
  unit_test_doubles_equal();
  unit_test_doubles_count_while();
  unit_test_doubles_count_while_not();
  unit_test_doubles_unique();
  unit_test_doubles_groups();
  unit_test_doubles_runs();
  unit_test_doubles_runs_not();
  unit_test_doubles_runs_starts();
  unit_test_doubles_runs_starts_not();
}