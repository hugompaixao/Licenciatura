#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "our_ints.h"
#include "our_strings.h"

// A *************************************/
/*
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
*/
void esplanada() {/*
  int r, c;
  scanf("%d%d", &r, &c);
  int m[r][c];
  matrix_clear(r, c, m);
  getTables(r, c, m);

  Table *table1[10000];
  int length = buildStruct(r, c, m, table1);
  Table *table2[10000];
  int n = getCloserTable(r, c, m, table1, length, table2);
  isort(table2, n);
  printf("%d %d %d\n", table2[0]->x, table2[0]->y, table2[0]->value);
*/}

// B *************************************/

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
  while(str[i] != '\0' && str[i] != ',') {
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

void resetage(VaccinationPlan **var, int length) {
  for(int i = 0; i < length; i++)
    if(var[i]->value == 1)
      var[i]->age -= 5;
    else
      var[i]->age -= 10;
}

void printVac(VaccinationPlan **var, int length) {
  for(int i = 0; i < length; i++) 
    printf("%s %d %d\n", var[i]->name, var[i]->age, var[i]->value);
}

void vacinas(const char *filename) {
  FILE *f = fopen(filename, "r");
  const char *str[10000];
  int length = strings_read(f, str);

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
  resetage(g1, leng1);

  printVac(g1, leng1);
  printVac(g2, leng2);
  printVac(g3, leng3);
}

// Main **************************************/

int main(int argc, char **argv) {
  int x = 'A';
  if(argc > 1)
    x = *argv[1];
  if(x == 'A')
    esplanada();
  else if(x == 'B')
    vacinas(argv[2]);
  else if("All unit tests PASSED.\n")
  return 0;
}