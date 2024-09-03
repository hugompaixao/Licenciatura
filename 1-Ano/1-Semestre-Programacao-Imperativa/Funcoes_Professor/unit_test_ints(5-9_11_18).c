// Ficheiro dado na semana de 5 - 9 de Novembro de 2018

//
//  our_ints_unit_tests_main.c
//
//  Created by Pedro Guerreiro on 01/11/2018.
//  Copyright © 2018 Pedro Guerreiro. All rights reserved.
//
// This just runs the unit tests from our_ints.c

// Compile with
// gcc -Wall our_ints_unit_tests.c our_ints.c -o our_ints_unit_tests.out

#include <stdio.h>

#include "our_ints.h"

// test:
// #include "header_file_test.h"

int main(int argc, char **argv)
{
  ints_unit_tests();
  int x = 'A';
  if (argc > 1)
    x = *argv[1];
  if (x == 'U')
    printf("All unit tests PASSED.\n");
  return 0;
}