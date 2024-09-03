//
//  our_ints.c
//
//  Created by Pedro Guerreiro on 01/11/2018.
//  Copyright © 2018 Pedro Guerreiro. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

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

// Write array elements on file, separated by separator
void ints_fprint(FILE *f, const int *a, int n, const char *separator)
{
  if (n > 0)
  {
    fprintf(f, "%d", a[0]);
    for (int i = 1; i < n; i++)  // i = 1
      fprintf(f, "%s%d", separator, a[i]);
  }
}

// Same as `ints_fprint` followed by newline
void ints_fprintln(FILE *f, const int *a, int n, const char *separator)
{
  ints_fprint(f, a, n, separator);
  fprintf(f, "\n");
}

// Write array elements on console, separated by separator
void ints_print(const int *a, int n, const char *separator)
{
  ints_fprint(stdout, a, n, separator);
}

// Same as `ints_print` followed by newline
void ints_println(const int *a, int n, const char *separator)
{
  ints_fprintln(stdout, a, n, separator);
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

// ---------------

// Create a dinamically allocated array with capacity `n`
int *ints_new(int n)
{
  //  return (int *) calloc(n, sizeof (int));
  return (int *) malloc (n * sizeof(int));
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
  int a[8] = {9,5,6,6, 5,7,5,3};
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
  int b[4] = {3,3,3,3};
  assert(ints_find(b, 4, 3) == 0);
  assert(ints_find(b, 4, 5) == -1);
}

// Index of the last occurrence of `x` in `a` or -1 if it does not occur.
int ints_find_last(const int *a, int n, int x)
{
  int result = n-1;
  while (result >= 0 && a[result] != x)
    result--;
  return result;
}

void unit_test_ints_find_last(void)
{
  int a[8] = {9,5,6,6, 5,7,5,3};
  assert(ints_find_last(a, 8, 9) == 0);
  assert(ints_find_last(a, 8, 5) == 6);
  assert(ints_find_last(a, 8, 6) == 3);
  assert(ints_find_last(a, 8, 7) == 5);
  assert(ints_find_last(a, 8, 3) == 7);
  assert(ints_find_last(a, 8, 2) == -1);
  assert(ints_find_last(a, 4, 7) == -1);
  assert(ints_find_last(a, 4, 5) == 1);
  assert(ints_find_last(a, 0, 9) == -1);
  assert(ints_find_last(a, 0, 4) == -1);
  int b[4] = {3,3,3,3};
  assert(ints_find_last(b, 4, 3) == 3);
  assert(ints_find_last(b, 4, 5) == -1);
}

// Array `b` shall contain the first ocurrence of each element of array `a`,
// in the same order.
int ints_nub(const int *a, int n, int *b)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    if (ints_find(b, result, a[i]) == -1)
      b[result++] = a[i];
  return result;
}

void unit_test_ints_nub(void)
{
  int a1[12] = {6,2,6,9, 4,2,9,9, 9,2,1,2};
  int b1[12];
  int m1 = ints_nub(a1, 12, b1);
  int z1[5] = {6,2,9,4,1};
  assert(ints_equal(b1, m1, z1, 5));
  
  int a2[6] = {1,2,3,3,2,1};
  int b2[6];
  int m2 = ints_nub(a2, 6, b2);
  int z2[3] = {1,2,3};
  assert(ints_equal(b2, m2, z2, 3));
  
  int a3[5] = {8,8,8,8,8};
  int b3[5];
  int m3 = ints_nub(a3, 5, b3);
  assert(m3 == 1 && b3[0] == 8);
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

// Copy array `a` to array `b`.
int ints_copy(const int *a, int n, int *b)
{
  if (n < 0)
    n = 0;
  memmove(b, a, n * sizeof(int));  // Note: 3rd arg is unsigned.
  return n;
}

// Random number from 0 (inclusive) to n (exclusive).
// Note: not tested in Windows.
int rand_to(int n)
{
  assert(n > 0);
  long long int m = RAND_MAX + 1L;
  // implicitly divide range [0..m[ into n ranges of w numbers:
  // [0..w[, [w..2*w[, [2*w..3*w[, ... [(n-1)*w, n*w[;
  long long int w = m / n;
  // random numbers greater or equal to limit are ignored:
  long long int limit = n * w;
  long long r;
  do
    r = rand();  // generate a random number
  while (r >= limit); // if greater than limit, ignore and repeat:
  // compute the number of the range to which r belongs
  // this is a number in the range [0..n[
  // it's the random number we wanted:
  return (int)(r / w);
}

// Create array wity n random numbers in [0..x[
int ints_random(int x, int n, int *a) // random numbers in [0..x[
{
  assert(x > 0);
  int result = 0;
  for (int i = 0; i < n; i++)
    a[result++] = rand_to(x);
  return result;
}

// --------------------

// Number of elements of `a` before first ocurrence of an element with value
// not equal to `x` or `n` if all elements are equal to `x`.
int ints_count_while(const int *a, int n, int x)
{
  int result = 0;
  while (result < n && a[result] == x)
    result++;
  return result;
}

void unit_test_ints_count_while(void)
{
  int a[16] = {4,4,4,3, 5,9,9,5, 5,5,5,5, 5,5,1,1};
  assert(ints_count_while(a, 16, 4) == 3);
  assert(ints_count_while(a, 16, 7) == 0);
  assert(ints_count_while(a+4, 12, 5) == 1);
  assert(ints_count_while(a+4, 12, 2) == 0);
  assert(ints_count_while(a+8, 8, 5) == 6);
  assert(ints_count_while(a+8, 8, 3) == 0);
  assert(ints_count_while(a+14, 2, 1) == 2);
  assert(ints_count_while(a+14, 2, 3) == 0);
}

// Number of elements of `a` before first ocurrence of an element with value
// equal to `x` or `n` if all elements not are equal to `x`.
int ints_count_while_not(const int *a, int n, int x)
{
  int result = 0;
  while (result < n && a[result] != x)
    result++;
  return result;
}

void unit_test_ints_count_while_not(void)
{
  int a[16] = {4,4,4,3, 5,9,9,5, 5,5,5,5, 5,5,1,5};
  assert(ints_count_while_not(a, 16, 4) == 0);
  assert(ints_count_while_not(a, 16, 5) == 4);
  assert(ints_count_while_not(a+4, 12, 5) == 0);
  assert(ints_count_while_not(a+4, 12, 1) == 10);
  assert(ints_count_while_not(a+8, 8, 5) == 0);
  assert(ints_count_while_not(a+8, 8, 1) == 6);
  assert(ints_count_while_not(a+8, 8, 3) == 8);
}

// Array `b` contains the first element of each run of equal elements
// in the array `a`, in the same order.
int ints_unique(const int *a, int n, int *b)
{
  int result = 0;
  int i = 0;
  while (i < n)
  {
    int z = ints_count_while(a+i, n-i, a[i]);
    b[result++] = a[i];
    i += z;
  }
  return result;
}


void unit_test_ints_unique(void)
{
  int a1[16] = {4,9,4,4, 4,7,7,7, 7,7,8,6, 6,6,6,4};
  int b1[16];
  int z1[7] = {4,9,4,7,8,6,4};
  int m1 = ints_unique(a1, 16, b1);
  assert(ints_equal(b1, m1, z1, 7));
  
  int a2[8] = {4,4,4,4, 4,4,4,4};
  int b2[8];
  int z2[1] = {4};
  int m2 = ints_unique(a2, 8, b2);
  assert(ints_equal(b2, m2, z2, 1));
}

// Array `b` contains the number of elements in each run of equal elements
// in the array `a`, in the same order.
int ints_groups(const int *a, int n, int *b)
{
  int result = 0;
  int i = 0;
  while (i < n)
  {
    int z = ints_count_while(a+i, n-i, a[i]);
    b[result++] = z;
    i += z;
  }
  return result;
}

void unit_test_ints_groups(void)
{
  int a1[16] = {4,9,4,4, 4,7,7,7, 7,7,8,6, 6,6,6,4};
  int b1[16];
  int z1[7] = {1,1,3,5,1,4,1};
  int m1 = ints_groups(a1, 16, b1);
  assert(ints_equal(b1, m1, z1, 7));
  
  int a2[8] = {4,4,4,4, 4,4,4,4};
  int b2[8];
  int z2[1] = {8};
  int m2 = ints_groups(a2, 8, b2);
  assert(ints_equal(b2, m2, z2, 1));
}

// Array `b` shall containt the length of each run of elements with
// value `x` in array `a`.
int ints_runs(const int *a, int n, int x, int *b)
{
  int result = 0;
  int i = 0;
  while (i < n)
    if (a[i] == x)
    {
      int z = ints_count_while(a+i, n-i, x);
      b[result++] = z;
      i += z;
    }
    else
      i++;
  return result;
}

void unit_test_ints_runs(void)
{
  int a1[24] = {4,9,4,4, 4,7,7,7, 7,7,8,6, 6,6,6,4, 7,4,4,6, 6,9,9,4};
  int b11[24];
  int m11 = ints_runs(a1, 24, 4, b11);
  int c11[5] = {1, 3, 1, 2, 1};
  assert(ints_equal(b11, m11, c11, 5));
  int b12[24];
  int m12 = ints_runs(a1, 24, 7, b12);
  int c12[2] = {5, 1};
  assert(ints_equal(b12, m12, c12, 2));
  int b13[24];
  int m13 = ints_runs(a1, 24, 8, b13);
  int c13[1] = {1};
  assert(ints_equal(b13, m13, c13, 1));
  int b14[24];
  int m14 = ints_runs(a1, 24, 5, b14);
  assert(m14 == 0);
  
  int a2[8] = {4,4,4,4, 4,4,4,4};
  int b21[8];
  int m21 = ints_runs(a2, 8, 4, b21);
  int c21[1] = {8};
  assert(ints_equal(b21, m21, c21, 1));
  int b22[8];
  int m22 = ints_runs(a2, 8, 5, b22);
  assert(m22 == 0);
}

// Array `b` shall containt the length of each run of `x` in array `a`,
// and array `c` shall contain the start position of each run.
int ints_runs_starts(const int *a, int n, int x, int *b, int *c)
{
  int result = 0;
  int i = 0;
  while (i < n)
    if (a[i] == x)
    {
      int z = ints_count_while(a+i, n-i, x);
      b[result] = z;
      c[result] = i;
      result++;
      i += z;
    }
    else
      i++;
  return result;
}

void unit_test_ints_runs_starts(void)
{
  int a1[24] = {4,9,4,4, 4,7,7,7, 7,7,8,6, 6,6,6,4, 7,4,4,6, 6,9,9,4};
  int b11[24];
  int c11[24];
  int m11 = ints_runs_starts(a1, 24, 4, b11, c11);
  int d11[7] = {1, 3, 1, 2, 1};
  int e11[7] = {0, 2, 15, 17, 23};
  assert(ints_equal(b11, m11, d11, 5));
  assert(ints_equal(c11, m11, e11, 5));
  int b12[24];
  int c12[24];
  int m12 = ints_runs_starts(a1, 24, 7, b12, c12);
  int d12[2] = {5, 1};
  int e12[2] = {5, 16};
  assert(ints_equal(b12, m12, d12, 2));
  assert(ints_equal(c12, m12, e12, 2));
  int b13[24];
  int c13[24];
  int m13 = ints_runs_starts(a1, 24, 8, b13, c13);
  int d13[1] = {1};
  int e13[1] = {10};
  assert(ints_equal(b13, m13, d13, 1));
  assert(ints_equal(c13, m13, e13, 1));
  int b14[24];
  int c14[24];
  int m14 = ints_runs_starts(a1, 24, 5, b14, c14);
  assert(m14 == 0);
  
  int a2[8] = {4,4,4,4, 4,4,4,4};
  int b21[8];
  int c21[8];
  int m21 = ints_runs_starts(a2, 8, 4, b21, c21);
  int d21[1] = {8};
  int e21[1] = {0};
  assert(ints_equal(b21, m21, d21, 1));
  assert(ints_equal(c21, m21, e21, 1));
  int b22[8];
  int c22[8];
  int m22 = ints_runs_starts(a2, 8, 5, b22, c22);
  assert(m22 == 0);
}

// --------------------------------------------

// Is the array sorted?
int ints_is_sorted(int *a, int n)
{
  for (int i = 1; i < n; i++)
    if (a[i-1] > a[i])
      return 0;
  return 1;
}

void unit_test_ints_is_sorted(void)
{
  int a[10] = {1,2,5,5,5, 6,8,8,9,9};
  assert(ints_is_sorted(a, 10));
  assert(ints_is_sorted(a, 1));
  assert(ints_is_sorted(a, 0));
  int b[10] = {3,5,5,2,4, 4,8,8,2,5};
  assert(!ints_is_sorted(b, 10));
  assert(ints_is_sorted(b, 3));
  assert(!ints_is_sorted(b, 5));
  assert(ints_is_sorted(b+3, 5));
  assert(!ints_is_sorted(b+5, 5));
}

// Rank of `x` in array `a`, logarithmically, assuming `a` is sorted
int ints_rank(const int *a, int n, int x)
{
  int result = 0;
  while (n > 0)
  {
    int m = n / 2;
    if (x <= a[m])
      n = m;
    else
    {
      result += m+1;
      a += m+1;
      n -= m+1;
    }
  }
  return result;
}

void unit_test_ints_rank(void)
{
  int a[12] = {2,2,3,5, 5,5,7,7, 10,10,15,18};
  assert(ints_rank(a, 12, 5) == 3);
  assert(ints_rank(a, 12, 7) == 6);
  assert(ints_rank(a, 12, 10) == 8);
  assert(ints_rank(a, 12, 9) == 8);
  assert(ints_rank(a, 12, 18) == 11);
  assert(ints_rank(a, 12, 20) == 12);
  assert(ints_rank(a, 12, 2) == 0);
  assert(ints_rank(a, 4, 9) == 4);
  assert(ints_rank(a, 4, 4) == 3);
  assert(ints_rank(a, 4, 2) == 0);
  assert(ints_rank(a, 1, 4) == 1);
  assert(ints_rank(a, 1, 1) == 0);
  assert(ints_rank(a, 0, 7) == 0);
  int b[12] = {5,5,5,5,5, 5,5,5,5,5};
  assert(ints_rank(b, 10, 4) == 0);
  assert(ints_rank(b, 10, 14) == 10);
}

// first index of x in `a`, using binary search, assuming a is sorted.
int ints_bfind(const int *a, int n, int x)
{
  int r = ints_rank(a, n, x);
  return r < n && a[r] == x ? r : -1;
}

void unit_test_ints_bfind(void)
{
  int a[12] = {2,2,3,5, 5,5,7,7, 10,10,15,18};
  assert(ints_bfind(a, 12, 5) == 3);
  assert(ints_bfind(a, 12, 7) == 6);
  assert(ints_bfind(a, 12, 10) == 8);
  assert(ints_bfind(a, 12, 9) == -1);
  assert(ints_bfind(a, 12, 18) == 11);
  assert(ints_bfind(a, 12, 20) == -1);
  assert(ints_bfind(a, 12, 2) == 0);
  assert(ints_bfind(a, 4, 9) == -1);
  assert(ints_bfind(a, 4, 4) == -1);
  assert(ints_bfind(a, 4, 2) == 0);
  assert(ints_bfind(a, 1, 4) == -1);
  assert(ints_bfind(a, 1, 1) == -1);
  assert(ints_bfind(a, 0, 7) == -1);
  int b[12] = {5,5,5,5,5, 5,5,5,5,5};
  assert(ints_bfind(b, 10, 4) == -1);
  assert(ints_bfind(b, 10, 14) == -1);
}

// Exchange the values of `a[x]` and `a[y]`.
void ints_exchange(int *a, int x, int y)
{
  int m = a[x];
  a[x] = a[y];
  a[y] = m;
}

// Private function: sort array `a`, provided a[0], a[1], ... a[n-2] is sorted.
void ints_sort_last(int *a, int n)
{
  int i = n-1;
  while (i > 0 && a[i-1] > a[i])
  {
    ints_exchange(a, i-1, i);
    i--;
  }
}

// Insert `x` in sorted array `a`.
int ints_insert(int *a, int n, int x)
{
  int result = n;
  a[result++] = x;
  ints_sort_last(a, result);
  return result;
}

void unit_test_ints_insert(void)
{
  int a1[10] = {2,2,3,5,5,9};
  int m1 = ints_insert(a1, 6, 4);
  int b1[7] = {2,2,3,4,5,5,9};
  assert(ints_equal(a1, m1, b1, 7));
  int a2[10] = {2,2,3,5,5,9};
  int m2 = ints_insert(a2, 6, 0);
  int b2[7] = {0,2,2,3,5,5,9};
  assert(ints_equal(a2, m2, b2, 7));
  int a3[10] = {2,2,3,5,5,9};
  int m3 = ints_insert(a3, 6, 20);
  int b3[7] = {2,2,3,5,5,9,20};
  assert(ints_equal(a3, m3, b3, 7));
  int a4[10] = {2,2,3,5,5,9};
  int m4 = ints_insert(a4, 6, 5);
  int b4[7] = {2,2,3,5,5,5,9};
  assert(ints_equal(a4, m4, b4, 7));
  int a5[10] = {};
  int m5 = ints_insert(a5, 0, 90);
  int b5[1] = {90};
  assert(ints_equal(a5, m5, b5, 1));
}

// Sort array `a` using insertionsort
void ints_isort(int *a, int n)
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && a[j-1] > a[j])
    {
      ints_exchange(a, j-1, j);
      j--;
    }
  }
}

void unit_test_ints_isort(void)
{
  int a1[7] = {9,5,2,4,5,3,2};
  ints_isort(a1, 7);
  int b1[7] = {2,2,3,4,5,5,9};
  assert(ints_equal(a1, 7, b1, 7));
  int a2[2] = {8,3};
  ints_isort(a2, 2);
  int b2[2] = {3,8};
  assert(ints_equal(a2, 2, b2, 2));
  int a3[16] = {9,5,17,2, 17,6,5,2, 8,12,18,1, 2,7,19,9};
  ints_isort(a3, 16);
  int b3[16] = {1,2,2,2, 5,5,6,7, 8,9,9,12, 17,17,18,19};
  assert(ints_equal(a3, 16, b3, 16));
}

// Merge sorted arrays `a` and `b`, yielding `c`.
int ints_merge(const int *a, int n, const int *b, int m, int *c)
{
  int result = 0;
  int i = 0;
  int j = 0;
  while (i < n && j < m)
    if (a[i] <= b[j])
      c[result++] = a[i++];
    else
      c[result++] = b[j++];
  result += ints_copy(a + i, n - i, c+result);
  result += ints_copy(b + j, m - j, c+result);
  return result;
}

void unit_test_ints_merge(void)
{
  int a1[3] = {2,4,7};
  int b1[4] = {2,3,5,9};
  int c1[7];
  int m1 = ints_merge(a1, 3, b1, 4, c1);
  int d1[7] = {2,2,3,4,5,7,9};
  assert(ints_equal(c1, m1, d1, 7));
  int a2[3] = {2,4,7};
  int b2[0] = {};
  int c2[3];
  int m2 = ints_merge(a2, 3, b2, 0, c2);
  assert(ints_equal(c2, m2, a2, 3));
}

// Private function: sort array `a`, using array `b` for temporary array result.
void ints_msort_i(int *a, int n, int *b)
{
  if (n > 1)
  {
    int m = n / 2;
    ints_msort_i(a, m, b);
    ints_msort_i(a+m, n-m, b);
    ints_merge(a, m, a+m, n-m, b);
    ints_copy(b, n, a);
  }
}

// Sort array `a` using mergesort.
void ints_msort(int *a, int n)
{
  int *b = ints_new(n);
  ints_msort_i(a, n, b);
}

void unit_test_ints_msort(void)
{
  int a1[7] = {9,5,2,4,5,3,2};
  ints_msort(a1, 7);
  int b1[7] = {2,2,3,4,5,5,9};
  assert(ints_equal(a1, 7, b1, 7));
  int a2[2] = {8,3};
  ints_msort(a2, 2);
  int b2[2] = {3,8};
  assert(ints_equal(a2, 2, b2, 2));
  int a3[16] = {9,5,17,2, 17,6,5,2, 8,12,18,1, 2,7,19,9};
  ints_msort(a3, 16);
  int b3[16] = {1,2,2,2, 5,5,6,7, 8,9,9,12, 17,17,18,19};
  assert(ints_equal(a3, 16, b3, 16));
}

// --------------------------

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
  unit_test_ints_find_last();
  unit_test_ints_nub();
  unit_test_ints_equal();
  
  unit_test_ints_count_while();
  unit_test_ints_count_while_not();
  unit_test_ints_insert();
  unit_test_ints_unique();
  unit_test_ints_groups();
  unit_test_ints_runs();
  unit_test_ints_runs_starts();
  
  unit_test_ints_is_sorted();
  unit_test_ints_rank();
  unit_test_ints_bfind();
  unit_test_ints_insert();
  unit_test_ints_isort();
  unit_test_ints_merge();
  unit_test_ints_msort();
}