// Ficheiro dado na semana de 5 - 9 de Novembro de 2018

//
//  our_ints.h
//
//  Created by Pedro Guerreiro on 01/11/2018.
//  Copyright © 2018 Pedro Guerreiro. All rights reserved.
//

#ifndef our_ints_h
#define our_ints_h

void ints_println_basic(const int *a, int n);
void ints_println_special(const int *a, int n);
int ints_get(int *a);
int ints_get_until(int terminator, int *a);
int ints_get_some(int *a, int n);
int ints_fill(int x, int n, int *a);
int ints_count(const int *a, int n, int x);
int ints_sum(const int *a, int n);
int ints_mean(const int *a, int n);
int ints_remove(const int *a, int n, int x, int *b);
int ints_max(const int *a, int n);
int ints_min(const int *a, int n);
int ints_argmax(const int *a, int n);
int ints_argmin(const int *a, int n);
int ints_indices(const int *a, int n, int x, int* b);
int ints_find(const int *a, int n, int x);
int ints_equal(const int *a, const int n, const int *b, int m);

void unit_test_ints_count(void);
void unit_test_ints_sum(void);
void unit_test_ints_remove(void);
void unit_test_ints_max(void);
void unit_test_ints_min(void);
void unit_test_ints_argmax(void);
void unit_test_ints_argmin(void);
void unit_test_ints_indices(void);
void unit_test_ints_find(void);
void unit_test_ints_equal(void);

void ints_unit_tests(void);

#endif