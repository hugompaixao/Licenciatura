// Ficheiro dado na semana de 5 - 9 de Novembro de 2018

//
//  our_ints.c
//
//  Created by Pedro Guerreiro on 01/11/2018.
//  Copyright © 2018 Pedro Guerreiro. All rights reserved.
//

#include <stdio.h>
#include <assert.h>

#include "our_ints.h"

// Write array elements in a line, separated by a space.
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

// Like ints_println_basic, but empty arrays are represented
// by a line with an asterisk.
void ints_println_special(const int *a, int n)
{
  if (n == 0)
    printf("*\n");
  else
    ints_println_basic(a, n);
}

// Read array elements until no more items exists for reading.
int ints_get(int *a)
{
  int result = 0;
  int x;
  while (scanf("%d", &x) != EOF)
    a[result++] = x;
  return result;
}

// Read array elements until a terminator value is read
// or until no more items exist for reading.
// The terminator is NOT read into the array.
int ints_get_until(int terminator, int *a)
{
  int result = 0;
  int x;
  while (scanf("%d", &x) != EOF && x != terminator)
    a[result++] = x;
  return result;
}

// Read at most `n` array elements
// or until no more items exist for reading, whichever happens first.
int ints_get_some(int *a, int n)
{
  int result = 0;
  int x;
  while (result < n && scanf("%d", &x) != EOF)
    a[result++] = x;
  return result;
}

// The first `n` elements of `a` will have value `x`.
int ints_fill(int x, int n, int *a)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    a[result++] = x;
  assert(result == n);
  return result;
}

// How many elements of `a` have value `x`?
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

// Sum of all elements of the array.
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

// Average of the array
int ints_mean(const int *a, int n)
{
  assert(n > 0);
  return ints_sum(a, n) / n;
}

// Array `b` has all elements of `a`, except those with value `x`, in the
// same order.
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
  int c1[3] = {6,1,8};
  assert(ints_equal(b1, m1, c1, 3));
  int b2[5];
  int m2 = ints_remove(a, 5, 6, b2);
  int c2[4] = {7,1,8,7};
  assert(ints_equal(b2, m2, c2, 4));
  int b3[5];
  int m3 = ints_remove(a, 5, 3, b3);
  assert(ints_equal(b3, m3, a, 5));
  int b4[5];
  int m4 = ints_remove(a, 0, 7, b4);
  assert(m4 == 0);
 }

// Max value of non-empty array.
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

// Min value of non-empty array.
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

// Index of first ocurrence of the max value in the array.
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

// Index of first ocurrence of the min value in the array.
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

// Array of the positions of `x` in `a`.
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
  int m11 = ints_indices(a1, 16, 5, b11);
  int c11[4] = {1,4,5,15};
  assert(ints_equal(b11, m11, c11, 4));
  int b12[16];
  int m12 = ints_indices(a1, 16, 1, b12);
  int c12[4] = {0, 12, 13};
  assert(ints_equal(b12, m12, c12, 3));
  int b13[16];
  int m13 = ints_indices(a1, 16, 3, b13);
  assert(m13 == 1 && b13[0] == 7);
  int b14[16];
  int m14 = ints_indices(a1, 16, 8, b14);
  assert(m14 == 0);
  int b15[16];
  int m15 = ints_indices(a1, 0, 5, b15);
  assert(m15 == 0);

  int a2[5] = {4,4,4,4,4};
  int b21[5];
  int m21 = ints_indices(a2, 6, 4.0, b21);
  int c21[5] = {0,1,2,3,4};
  assert(ints_equal(b21, m21, c21, 5));
  int b22[5];
  int m22 = ints_indices(a2, 6, 5.0, b22);
  assert(m22 == 0);
}

// Index of the first occurrence of `x` in `a` or -1 if it does not occur.
int ints_find(const int *a, int n, int x)
{
  for (int i = 0; i < n; i++)
    if (a[i] == x)
      return i;
  return -1;
}

void unit_test_ints_find(void)
{
  int a[] = {9,5,6,6, 5,7,5,3};
  int b[] = {3,3,3,3};
  assert(ints_find(a, 8, 9) == 0);
  assert(ints_find(a, 8, 5) == 1);
  assert(ints_find(a, 8, 6) == 2);
  assert(ints_find(a, 8, 7) == 5);
  assert(ints_find(a, 8, 3) == 7);
  assert(ints_find(a, 8, 2) == -1);
  assert(ints_find(a, 4, 7) == -1);
  assert(ints_find(a, 4, 5) == 1);
  assert(ints_find(a, 0, 9) == -1);
  assert(ints_find(a, 0, 4) == -1);
  assert(ints_find(b, 4, 3) == 0);
  assert(ints_find(b, 4, 5) == -1);
}

// Are the two arrays equal?
int ints_equal(const int *a, const int n, const int *b, int m)
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

void unit_test_ints_equal(void)
{
  int a[] = {7, 4, 1, 5};
  int b[] = {7, 4, 2, 7, 5};
  int c[] = {4, 1, 5, 7};
  int d[] = {4, 1, 5, 8};
  assert(ints_equal(a, 4, a, 4));
  assert(ints_equal(a, 2, b, 2));
  assert(ints_equal(c, 3, d, 3));
  assert(ints_equal(a, 0, c, 0));
  assert(!ints_equal(a, 3, c, 2));
  assert(!ints_equal(a, 4, b, 5));
  assert(!ints_equal(c, 4, d, 4));
  assert(!ints_equal(a, 3, b, 3));
}

void ints_unit_tests(void)
{
  unit_test_ints_count();
  unit_test_ints_sum();
  unit_test_ints_remove();
  unit_test_ints_max();
  unit_test_ints_min();
  unit_test_ints_argmax();
  unit_test_ints_argmin();
  unit_test_ints_indices();
  unit_test_ints_find();
  unit_test_ints_equal();
}