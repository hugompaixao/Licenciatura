#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "our_ints.h"

#define MAX_OUTPUT 10000

void matrix_clear(int r, int c, int m[r][c]) {
  ints_clear((int *)m, r*c);
}

// Alcochete 2021 ******************************************/
typedef struct {
  int x, y, value;
} Coordinates;

Coordinates *coordinates(int x, int y, int value) {
  Coordinates *result = (Coordinates *) malloc(sizeof(Coordinates));
  result->x = x;
  result->y = y;
  result->value = value;
  return result;
}

void printCoordinates(Coordinates **coordinate, int length) {
  for(int i = 0; i < length; i++)
    printf("%d %d %d\n", coordinate[i]->x, coordinate[i]->y, coordinate[i]->value);
}

void placeTrees(int r, int c, int m[r][c]) {
  int x, y;
  while(scanf("%d%d", &x, &y) != EOF)
    m[y][x]++; 
}

int countTrees(int r, int c, int m[r][c], int h, int v, int x, int y) {
  int result = 0;
  for(int i = 0; i < v; i++) {
    for(int j = 0; j < h; j++)
      result += m[i+y][j+x];
  }
  return result;
}

int treesByPlace(int H, int V, int m[V][H], int C, int A, Coordinates **coordinate) {
  int result = 0;
  int finalH = H - C + 1;
  int finalV = V - A + 1;
  for(int i = 0; i < finalV; i++) {
    for(int j = 0; j < finalH; j++)
      coordinate[result++] = coordinates(j, i, countTrees(V, H, m, C, A, j, i));
  }
  return result;
}

void exchangePointers(Coordinates **coordinate, int i, int j) {
  Coordinates *tmp = coordinate[i];
  coordinate[i] = coordinate[j];
  coordinate[j] = tmp;
}

void insertionSort(Coordinates **coordinate, int length) {
  for(int i = 1; i < length; i++) {
    int j = i;
    while(j > 0 && coordinate[j-1]->value > coordinate[j]->value) {
      exchangePointers(coordinate, j-1, j);
      j--;
    }
  }
}

void testValues(int H, int V, int C, int A) {
  assert(H > 0 && H <= 100);
  assert(V > 0 && V <= 100);
  assert(C > 0 && C <= H);
  assert(A > 0 && A <= V);
}

void alcochete2021() {
  int H, V, C, A;
  scanf("%d%d%d%d", &H, &V, &C, &A);
  testValues(H, V, C, A);

  int m[V][H];
  matrix_clear(V, H, m);

  placeTrees(V, H, m);
  Coordinates *coordinate[10000];
  int length = treesByPlace(H, V, m, C, A, coordinate);
  insertionSort(coordinate, length);
  printCoordinates(coordinate, length);
}

// Estudo de Promenor ***********************/

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

void coordenada_write(Coord *coord, int n) {
  for (int i = 0; i < n; i++){
    printf("%d %d %d\n", coord[i].x, coord[i].y, coord[i].value);
  }
}

int ints_partial_accumulate(int Upi, int Upj, int lowi, int lowj, int r, int c, int a[r][c]) 
{ 
    int result = a[lowi][lowj];
    if (Upi > 0) 
       result = result - a[Upi-1][lowj]; 
    if (Upj > 0) 
       result = result - a[lowi][Upj-1]; 
    if (Upi > 0 && Upj > 0) 
       result = result + a[Upi-1][Upj-1]; 
    return result; 
}

void int2_accumulate(int rows, int cols, int a[rows][cols], int b[rows][cols])
{
  b[0][0] = a[0][0]; 
  for (int i = 1; i < cols; i++) 
      b[0][i] = b[0][i - 1] + a[0][i]; 
  for (int i = 1; i < rows; i++)
      b[i][0] = b[i - 1][0] + a[i][0]; 
  for (int i = 1; i < rows; i++) 
    for (int j = 1; j < cols; j++) 
      b[i][j] = b[i-1][j] + b[i][j-1] - b[i-1][j-1] + a[i][j];
}

int cmp_Alco(const Coord a, const Coord b) {
  int r = a.value - b.value;
  if (r == 0){
    r = a.y - b.y;
    if(r == 0)
      r = a.x - b.x;
  }
return r;
}


int novas_coordenada(Coord *a, int H, int V, int C, int A, int r, int c, int m[r][c])//int *output
{
  int result = 0;
  for (int i = 0; i+A<=V ; i++)
  {
    for (int j = 0; j+C<=H ; j++)
    {
      a[result++] = coords(j, i, ints_partial_accumulate(i, j, i+(A-1), j+(C-1), V, H, m));
    }
  }  
  return result;
}

// Copy array `a` to array `b`.
int int_copy(const Coord *a, int n, Coord *b)
{
  if (n < 0)
    n = 0;
  memmove(b, a, n * sizeof(Coord));  // Note: 3rd arg is unsigned.
  return n;
}


// Merge sorted arrays `a` and `b`, yielding `c`.
int int_merge(const Coord *a, int n, const Coord *b, int m, Coord *c)
{
  int result = 0;
  int i = 0;
  int j = 0;
  while (i < n && j < m)
    if (cmp_Alco(a[i], b[j]) <= 0)
      c[result++] = a[i++];
    else
      c[result++] = b[j++];
  result += int_copy(a + i, n - i, c+result);
  result += int_copy(b + j, m - j, c+result);
  return result;
}

void int_msort_i(Coord *a, int n, Coord *b)
{
  if (n > 1)
  {
    int m = n / 2;
    int_msort_i(a, m, b);
    int_msort_i(a+m, n-m, b);
    int_merge(a, m, a+m, n-m, b);
    int_copy(b, n, a);
  }
}



// Sort array `a` using mergesort.
void int_msort(Coord *a, int n, int G)
{
  Coord *b = (Coord *)malloc( G * sizeof(Coord));
  int_msort_i(a, n, b); 
  free(b);  
}


void test_estudo_de_pormenor(void) {
  int H, V; // lado horizontal e vertical da AREA
  scanf("%d %d", &H, &V);
  int C, A; // lado horizontal e vertical da PISTA
  scanf("%d %d", &C, &A);
  int G = (H-C+1)*(V-A+1);
  // printf("%d\n", G);
  int M[V][H];
  matrix_clear(V, H, M);
  placeTrees(V, H, M);
  // ints2_printf(" %d", M, V, H);
  //  printf("\n");

  int matriz_acumulada[V][H];
  int2_accumulate(V, H, M, matriz_acumulada);
  // ints2_printf(" %d", matriz_acumulada, V, H);
  // printf("\n");
  


  Coord *coordenada =  malloc((G) * sizeof(Coord)); //estrutura de output
  int n_linhas = novas_coordenada(coordenada, H, V, C, A, V, H, matriz_acumulada);
  // coordenada_write(coordenadas, n_linhas);
  
  int_msort(coordenada, n_linhas, G);

  if (n_linhas > MAX_OUTPUT){
    coordenada_write(coordenada, MAX_OUTPUT);
    // printf("ola");
    }
  else
    coordenada_write(coordenada, n_linhas);
}


// Main **************************************/

int main(int argc, char **argv) {
  int x = 'A';
  if(argc > 1)
    x = *argv[1];
  if(x == 'A')
    alcochete2021();
  else if(x == 'B')
    test_estudo_de_pormenor();
  else if("All unit tests PASSED.\n")
  return 0;
}