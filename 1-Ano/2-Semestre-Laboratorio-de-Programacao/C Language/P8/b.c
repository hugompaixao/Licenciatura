#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "our_strings.h"

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

    var[result++] = vaccinationPlan(tmp, num, pat);
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
    if(var[i]->age >= 65 && var[i]->age <= 79)
      g[result++] = var[i];
  }
  return result;
}

int secondg(VaccinationPlan **var, int length, VaccinationPlan **g) {
  int result = 0;
  for(int i = 0; i < length; i++) {
    if(var[i]->age >= 50 && var[i]->age <= 64) {
      if(var[i]->value == 1)
        g[result++] = vaccinationPlan(var[i]->name, var[i]->age+5, var[i]->value);
      else if(var[i]->value >= 2)
        g[result++] = vaccinationPlan(var[i]->name, var[i]->age+10, var[i]->value);
    }
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

  printVac(g1, leng1);
  printVac(g2, leng2);
  printVac(g3, leng3);
}

int main(int argc, char **argv) {
  int x = 'A';
  if(argc > 1)
    x = *argv[1];

  if(x == 'A')
  vacinas(argv[2]);
  return 0;
}