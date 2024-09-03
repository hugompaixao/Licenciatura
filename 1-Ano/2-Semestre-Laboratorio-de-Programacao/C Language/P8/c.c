#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "our_ints.h"

void matrix_clear(int r, int c, int m[r][c]) {
  ints_clear((int *)m, r*c);
}

typedef struct {
  int x, y, value;
} Table;

Table *tables(int x, int y, int value) {
  Table *result = (Table *) malloc(sizeof(Table));;
  result->x = x;
  result->y = y;
  result->value = value;
  return result;
}

void getTables(int r, int c, int m[r][c]) {
  int x, y, z;
  while(scanf("%d%d%d", &x, &y, &z) != EOF)
    m[x][y] = z;
}

int buildStruct(int r, int c, int m[r][c], Table **table) {
  int result = 0;
  for(int i = 0; i < r; i++) {
    for(int j = 0; j < c; j++) {
      if(m[i][j] != 0)
        table[result++] = tables(i, j, m[i][j]);
    }
  }
  return result;
}

int distance(int x, int y, Table **table, int length) {
  int result = 0;
  for(int i = 0; i < length; i++) {
    int tmpx = abs(x - table[i]->x);
    int tmpy = abs(y - table[i]->y);
    result += (tmpx +tmpy)*table[i]->value;
  }
  return result;
}


int getCloserTable(int r, int c, int m[r][c], Table **table, int length, Table **final) {
  int result = 0;
  for(int i = 0; i < r; i++) {
    for(int j = 0; j < c; j++) {
      if(m[i][j] == 0) {
        final[result++] = tables(i, j, distance(i, j, table, length));
     } }
  }
  return result;
}

int cmp(Table *a, Table *b) {
  int result = b->value - a->value;
  if(result == 0) {
    result = a->x - b->x;
    if(result == 0)
      result = a->y - b->y;
  }
  return result;
}

void exchange(Table **table, int i, int j) {
  Table *tmp = table[i];
  table[i] = table[j];
  table[j] = tmp;
}

void isort(Table **table, int length) {
  for(int i = 0; i < length; i++) {
    int j = i;
    while(j > 0 && cmp(table[j-1], table[j]) > 0) {
      exchange(table, j-1, j);
      j--;
    }
  }
}

void esplanada() {
  int r, c;
  scanf("%d%d", &r, &c);
  int m[r][c];
  matrix_clear(r, c, m);
  getTables(r, c, m);

  Table *table1[10000];
  int length = buildStruct(r, c, m, table1);
  Table *table2[10000];
  int n = getCloserTable(r, c, m, table1, length, table2);
  //printf("%d\n", n);
  isort(table2, n);
  /*for(int i = 0; i < n; i++) {
    printf("%d %d %d\n", table2[i].x, table2[i].y, table2[i].value);
  }
  printf("\n");*/
  printf("%d %d %d\n", table2[0]->x, table2[0]->y, table2[0]->value);
}

int main() {
  esplanada();
  return 0;
}