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

void printCoords(Coord *coord, int length) {
  for(int i = 0; i < length; i++) {
    printf("%d %d %d\n", coord[i].x, coord[i].y, coord[i].value);
  }
}

int cmp(const Coord coordinate, const Coord coordinate2) {
  int result = coordinate.value - coordinate2.value;
  if (result == 0){
    result = coordinate.y - coordinate2.y;
    if(result == 0)
      result = coordinate.x - coordinate2.x;
  }
  return result;
}

int ints_partial_accumulate(int r, int c, int m[r][c], int Upi, int Upj, int lowi, int lowj) { 
    int result = m[lowi][lowj];
    if (Upi > 0) 
       result = result - m[Upi-1][lowj]; 
    if (Upj > 0) 
       result = result - m[lowi][Upj-1]; 
    if (Upi > 0 && Upj > 0) 
       result = result + m[Upi-1][Upj-1]; 
    return result; 
}

void ints2_accumulate(int r, int c, int m[r][c], int m2[r+1][c+1]) {
  for(int i = 0; i < r+1; i++) 
    m2[i][0] = 0;

  for(int j = 1; j < c+1; j++)  
    m2[0][j] = 0;

  for(int i = 0; i < r; i++)
    for(int j = 0; j < c; j++)
      m2[i+1][j+1] = m[i][j] + m2[i][j+1] + m2[i+1][j] - m2[i][j];
}

int getTrees(int H, int V, int C, int A, int m[V][H], int m2[V][H], Coord *coord) {
  int result = 0;
  for(int i = 0; i+A <= V; i++) {
    for(int j = 0; j+C <= H; j++)
      coord[result++] = coords(j, i, ints_partial_accumulate(V, H, m, i, j, i+(A-1), j+(C-1)));
  }
  return result;
}

int copy(const Coord *coord, int length, Coord *coord2) {
  if(length < 0)
    length = 0;
  
  memmove(coord2, coord, length * sizeof(Coord));
  return length;
}

int imerge(const Coord *coord, int length, const Coord *coord2, int len, Coord *coord3) {
  int result = 0, i = 0, j = 0;
  while(i < length && j < len) {
    if(cmp(coord[i], coord2[j]) <= 0)
      coord3[result++] = coord[i++];
    else
      coord3[result++] = coord2[j++];
  }
  result += copy(coord + i, length - i, coord3 + result);
  result += copy(coord2 + j, len - j, coord3 + result);
  return 
  result;
}

void msort_i(Coord *coord, int length, Coord *coord2) {
  if(length > 1) {
    int len = length / 2;
    msort_i(coord, len, coord2);
    msort_i(coord + len, length - len, coord2);
    imerge(coord, len, coord + len, length - len, coord2);
    copy(coord2, length, coord);
  }
}

void msort(Coord *coord, int length, int size) {
  Coord *tmp = (Coord *) malloc(size * sizeof(Coord));
  msort_i(coord, length, tmp);
  free(tmp);
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
  testValuesTwo(H, V, C, A);
  int size = (H-C+1)*(V-A+1);

  int m[V][H];
  int m2[V][H];
  matrix_clear(V, H, m);
  placeTrees(V, H, m);
  ints2_accumulate(V, H, m, m2);

  Coord *coord = malloc((size) * sizeof(Coord));
  int length = getTrees(H, V, C, A, m, m2, coord);

  msort(coord, length, size);

  if(length > MAX_OUTPUT)
    printCoords(coord, MAX_OUTPUT);
  else
    printCoords(coord, length);
}

int main() {
  estudo_de_Promenor();
  return 0;
}















/*typedef struct {
  int x, y, value;
} Coord;

Coord coords(int x, int y, int value) {
  Coord result;
  result.x = x; 
  result.y = y;
  result.value = value;
  return result;
}

void accumulate(int r, int c, int m[r][c], int m2[r+1][c+1]) {
  for(int i = 0; i < r+1; i++) 
    m2[i][0] = 0;
  for(int j = 1; j < c+1; j++)  
    m2[0][j] = 0;
  for(int i = 0; i < r; i++)
    for(int j = 0; j < c; j++)
      b[i+1][j+1] = m[i][j] + m2[i][j+1] + m2[i+1][j] - m2[i][j];
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
  matrix_clear(V+1, H+1, m2);
  placeTrees(V, H, m):
  accumulate(V, H, m, m2);

}*/