#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "our_ints.h"

#define MAX_OUTPUT 10000

void matrix_clear(int r, int c, int m[r][c]) {
  ints_clear((int *)m, r*c);
}

void placeTrees(int r, int c, int m[r][c]) {
  int x, y;
  while(scanf("%d%d", &x, &y) != EOF)
    m[y][x]++; 
}



typedef struct {
  int x, y, value;
} Coord;

Coord coords(int x, int y, int value) {
  Coord result;
  result.x = x;
  result.y = y;
  result.value = value;
  return result;
}

Coord *coordsNew(int length) {
  return (Coord *) malloc(length * sizeof(Coord));
}

void matrix_accumulate(int r, int c, int m[r][c], int m2[r+1][c+1]) {
  for(int i = 0; i < r+1; i++) 
    m2[i][0] = 0;
  for(int j = 1; j < c+1; j++)  
    m2[0][j] = 0;
  for(int i = 0; i < r; i++)
    for(int j = 0; j < c; j++)
      m2[i+1][j+1] = m[i][j] + m2[i][j+1] + m2[i+1][j] - m2[i][j];
}

int accumulate(int H, int V, int C, int A, int m[V][H], Coord *coord) {
  int result = 0, sum = 0;
  int finalV = V - A;
  int finalH = H - C;
  for(int i = 0; i < finalV; i++) {
    for(int j = 0; j < finalH; j++) {
      sum = m[j+A][i+C] - m[j+A][i] - m[j][i+C] + m[j][i];
      coord[result++] = coords(j, i, sum);
    }
  }
  return result;
}

int cmp_estudo(Coord coord1, Coord coord2) {
  int result = coord1.value - coord2.value;
  if(result == 0) {
    result = coord1.y - coord2.y;
    if(result == 0)
      result = coord1.x - coord2.x;
  }
  return result;
}

int copy(const Coord *coord1, int length, Coord *coord2) {
  if(length < 0)
    length = 0;
  memmove(coord2, coord1, length * sizeof(Coord));
  return length;
}

int merge(const Coord *coord1, int length, const Coord *coord2, int len, int cmp(Coord, Coord), Coord *coord3) {
  int result = 0, i = 0, j = 0;
  while(i < length && j < len) {
    if(cmp(coord1[i], coord2[j]) <= 0)
      coord3[result++] = coord1[i++];
    else
      coord3[result++] = coord2[j++];
  }
  result += copy(coord1 + i, length - i, coord3 + result);
  result += copy(coord2 + j, len - j, coord3 + result);
  return result;
}

void msort_i(Coord *coord, int length, int cmp(Coord, Coord), Coord * coord2) {
  if(length > 1) {
    int len = length / 2;
    msort_i(coord, length, cmp, coord2);
    msort_i(coord + len, length - len, cmp, coord2);
    merge(coord, len, coord + len, length - len, cmp, coord2);
    copy(coord2, length, coord);
  }
}

void msort(Coord *coord, int length, int cmp(Coord, Coord)) {
  Coord *tmp = coordsNew(length);
  msort_i(coord, length, cmp, tmp);
  free(tmp);
}

void printCoords(Coord *coord, int length) {
  for(int i = 0; i < length; i++) 
    printf("%d %d %d\n", coord[i].x, coord[i].y, coord[i].value);
}

void testValuesTwo(int H, int V, int C, int A) {
  assert(H > 0 && H <= 1000);
  assert(V > 0 && V <= 1000);
  assert(C > 0 && C <= H);
  assert(A > 0 && A <= V);
}

void estudo_de_Promenor() {
  int H, V, C, A;
  scanf("%d%d%d%d", &H, &V, &C, &A);
  testValuesTwo(H, V, C , A);

  int m[V][H];
  int m2[V+1][H+1];
  matrix_clear(V, H, m);
  placeTrees(V, H, m);
  matrix_accumulate(V, H, m, m2);

  Coord *coord = coordsNew(1000000);
  int length = accumulate(H, V, A, C, m2, coord);
  printf("%d", length);
  msort(coord, length, cmp_estudo);

  if(length > MAX_OUTPUT)
    printCoords(coord, MAX_OUTPUT);
  else
    printCoords(coord, length);
}

int main() {
  estudo_de_Promenor();
  return 0;
}