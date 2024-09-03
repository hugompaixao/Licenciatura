// Ficheiro dado na semana de 19 - 23 de Novembro de 2018

//
//  our_doubles.h
//
//  Created by Pedro Guerreiro on 01/11/2018.
//  Copyright © 2018 Pedro Guerreiro. All rights reserved.
//

#ifndef our_doubles_h
#define our_doubles_h

void doubles_println_basic(const double *a, int n);
void doubles_println_special(const double *a, int n);
int doubles_get(double *a);
int doubles_get_until(double terminator, double *a);
int doubles_get_some(double *a, int n);
int doubles_fill(double x, int n, double *a);
int doubles_count(const double *a, int n, double x);
double doubles_sum(const double *a, int n);
double doubles_mean(const double *a, int n);
int doubles_remove(const double *a, int n, int x, double *b);
double doubles_max(const double *a, int n);
double doubles_min(const double *a, int n);
int doubles_argmax(const double *a, int n);
int doubles_argmin(const double *a, int n);
int doubles_indices(const double *a, int n, int x, int* b);
int doubles_find(const double *a, int n, double x);
int doubles_equal(const double *a, int n, const double *b, int m);

void unit_test_doubles_count(void);
void unit_test_doubles_sum(void);
void unit_test_doubles_remove(void);
void unit_test_doubles_max(void);
void unit_test_doubles_min(void);
void unit_test_doubles_argmax(void);
void unit_test_doubles_argmin(void);
void unit_test_doubles_indices(void);
void unit_test_doubles_find(void);
void unit_test_doubles_equal(void);

void doubles_unit_tests(void);

#endif