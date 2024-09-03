#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "our_ints.h"
#include "our_strings.h"

// Problem A *******************/

void matrix_clear(int r, int c, int m[r][c]) {
  ints_clear((int *)m, r*c);
}

typedef struct {
  int x, y, value;
} Esplanada;

Esplanada *esplanadas(int x, int y, int value) {
  Esplanada *result = (Esplanada *) malloc(sizeof(Esplanada));
  result->x = x;
  result->y = y;
  result->value = value;
  return result;
}

int getOccupation(int r, int c, int m[r][c], Esplanada **var) {
  int x, y, z, result = 0;
  while(scanf("%d%d%d", &x, &y, &z) != EOF) {
    m[x][y] = z;
    var[result++] = esplanadas(x, y, z);
  }
  return result;
}

int calculateDistance(int x, int y, Esplanada **var, int length) {
  int result = 0;
  for(int i = 0; i < length; i++) {
    int tmpX = abs(x - var[i]->x);
    int tmpY = abs(y - var[i]->y);
    result += (tmpX + tmpY) * var[i]->value;
  }
  return result;
}

int allPossiblePlace(int r, int c, int m[r][c], Esplanada **var, int length, Esplanada **final) {
  int result = 0;
  for(int i = 0; i < r; i++) {
    for(int j = 0; j < c; j++) {
      if(m[i][j] == 0)
        final[result++] = esplanadas(i, j, calculateDistance(i, j, var, length));
    }
  }
  return result;
}

int cmpDistances(Esplanada *var1, Esplanada *var2) {
  int result = var2->value - var1->value;
  if(result == 0) {
    result = var1->x - var2->x;
    if(result == 0)
      result = var1->y - var1->y;
  }
  return result;
}

void exchangeEsplanada(Esplanada **var, int i, int j) {
  Esplanada *tmp = var[i];
  var[i] = var[j];
  var[j] = tmp;
}

void isortEsplanada(Esplanada **var, int length) {
  for(int i = 1; i < length; i++) {
    int j = i;
    while(j > 0 && cmpDistances(var[j-1], var[j]) > 0) {
      exchangeEsplanada(var, j-1, j);
      j--;
    }
  }
}

void esplanada() {
  int r, c;
  scanf("%d%d", &r, &c);

  int m[r][c];
  matrix_clear(r, c, m);

  Esplanada *var[1000];
  int length = getOccupation(r, c, m, var);

  Esplanada *final[1000];
  int finalLength = allPossiblePlace(r, c, m, var, length, final);
  isortEsplanada(final, finalLength);
  printf("%d %d %d\n", final[0]->x, final[0]->y, final[0]->value);
}

// Problem B *******************/

typedef struct {
  const char *name;
  int age;
  int value;
} VaccinationPlan;

VaccinationPlan *vaccinationPlan(const char *name, int age, int value) {
  VaccinationPlan *result = (VaccinationPlan *) malloc(sizeof(VaccinationPlan));
  result->name = name;
  result->age = age;
  result->value = value;
  return result;
}

char *word(const char *str, char *tmp) {
  int i = 0, j = 0;
  while(str[i] != ',' && str[i] != '\0')
    tmp[j++] = str[i++];
  tmp[j] = '\0';
  return tmp;
}

char *substringByComa(const char *str, char *tmp) {
  int i = 0, j = 0;
  while(str[i] != ',' && str[i] != '\0')
    tmp[j++] = str[i++];
  tmp[j] = '\0';
  return tmp;
}

int comaIdx(const char *str) {
  int i = 0, idx = 0;
  while(str[i] != ',') {
    if(str[i+1] == ',')
      idx = i+2;
    i++;
  }
  return idx;
}

int countPat(const char *str) {
  int i = 0, result = 0;
  while(str[i] != '\0') {
    if(str[i] == ',')
      result++;
    i++;
  }
  result--;
  return result;
}

int buildStruct(const char **str, int length, VaccinationPlan **var) {
  int result = 0;
  for(int i = 0; i < length; i++) {
    char tmp[1000];
    char age[1000];
    substringByComa(str[i], tmp);
    int coma = comaIdx(str[i]);
    word(str[i]+coma, age);
    int num = atoi(age);
    int pat = countPat(str[i]);

    var[result++] = vaccinationPlan(str_dup(tmp), num, pat);
  }
  return result;
}

int firstg(VaccinationPlan **var, int length, VaccinationPlan **g) {
  int result = 0;
  for(int i = 0; i < length; i++) {
    if(var[i]->age >= 65 && var[i]->age <= 79) {
      if(var[i]->value == 1)
      g[result++] = vaccinationPlan(var[i]->name, (var[i]->age+5), var[i]->value);
     else if(var[i]->value >= 2)
        g[result++] = vaccinationPlan(var[i]->name, (var[i]->age+10), var[i]->value);
      else
        g[result++] = var[i];
    }
  }
  return result;
}

int secondg(VaccinationPlan **var, int length, VaccinationPlan **g) {
  int result = 0;
  for(int i = 0; i < length; i++) {
    if(var[i]->age >= 50 && var[i]->age <= 64 && var[i]->value != 0)
      g[result++] = var[i];
  }
  return result;
}

int thirdg(VaccinationPlan **var, int length, VaccinationPlan **g) {
  int result = 0;
  for(int i = 0; i < length; i++) {
    if(var[i]->age >= 80)
      g[result++] = var[i];
  }
  return result;
}

int cmp(const void *var, const void *var2) {
  VaccinationPlan *a = (VaccinationPlan *) var;
  VaccinationPlan *b = (VaccinationPlan *) var2;
  return (b->age - a->age);
}

void exchangeV(VaccinationPlan **var, int i, int j) {
  VaccinationPlan *tmp = var[i];
  var[i] = var[j];
  var[j] = tmp;
}

void isortV(VaccinationPlan **var, int length) {
  for(int i = 1; i < length; i++) {
    int j = i;
    while(j > 0 && var[j-1]->age - var[j]->age < 0) {
      exchangeV(var, j-1, j);
      j--;
    }
  }
}

void resetage(VaccinationPlan **var, int length) {
  for(int i = 0; i < length; i++)
    if(var[i]->value == 1)
      var[i]->age -= 5;
    else if(var[i]->value >= 2)
      var[i]->age -= 10;
}

void printVac(VaccinationPlan **var, int length) {
  for(int i = 0; i < length; i++) 
    printf("%s %d %d\n", var[i]->name, var[i]->age, var[i]->value);
}

void vacinas(const char *filename) {
  //FILE *f = fopen(filename, "r");
  const char *str[10000];
  int length = strings_read(stdin, str);

  VaccinationPlan *var[1000];
  int len = buildStruct(str, length, var);
  VaccinationPlan *g1[1000];
  int leng1 = firstg(var, len, g1);
  VaccinationPlan *g2[1000];
  int leng2 = secondg(var, len, g2);
  VaccinationPlan *g3[1000];
  int leng3 = thirdg(var, len, g3);

  isortV(g1, leng1);
  isortV(g2, leng2);
  isortV(g3, leng3);
  /*qsort(g1, leng1, sizeof(VaccinationPlan *), cmp);
  qsort(g2, leng2, sizeof(VaccinationPlan *), cmp);
  qsort(g3, leng3, sizeof(VaccinationPlan *), cmp);*/
  resetage(g1, leng1);

  printVac(g1, leng1);
  printVac(g2, leng2);
  printVac(g3, leng3);
}

// Problem C *******************/

void consignacao() {}

// Main ************************/
int main(int argc, char **argv) {
  int x = 'A';
  if(argc > 1)
    x = *argv[1];
  if(x == 'A')
    esplanada();
  else if(x == 'B')
    vacinas(argv[2]);
  else if(x == 'C')
    consignacao();
  else if("All unit tests PASSED.\n")
  return 0;
}