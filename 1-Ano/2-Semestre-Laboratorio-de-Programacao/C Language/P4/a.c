#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include<assert.h>

#include"our_ints.h"
#include"our_doubles.h"
#include"our_strings.h"

#define MAX 1000
/*----------------------------------------------------------------------------------- A --------------------------------------------------------------------------------*/

char *word(const char *str, char *tmp) {
  int i = 0, j = 0;
  while(str[i] != ' ' && str[i] != '\0')
    tmp[j++] = str[i++];
  tmp[j] = '\0';
  return tmp;
}

// given a string returns array of all words in that string
int string_split(const char *str, const char **words) {
  int result = 0, i = 0, count = 0;
  char tmp[MAX];
  while(str[i] != '\0') {
    if(str[i+1] == '\0'){
      words[result++] = str_dup(word(str+count, tmp));
      i++;
    }
    else if(str[i] == ' ') {
      words[result++] = str_dup(word(str+count, tmp));
      i++;
      count += i - count;
    } else 
      i++;
  }
  return result;
}

// given an array of strings get all words from all strings
int allWords(const char **str, int length, const char **words) {
  int result = 0;
  for(int i = 0; i < length; i++) {
    const char *tmp[MAX];
    int string_length = string_split(str[i], tmp);
    for(int j = 0; j < string_length; j++) 
      words[result++] = tmp[j];
  }
  return result;
}

// get names where there is a unique word
int names_with_unique_words(const char **str, int length, const char **words,
                              int allLenght, const char **unique) {
  int result = 0;
  for(int i = 0; i < length; i++) {
    const char *tmp[MAX];
    int string_length = string_split(str[i], tmp);
    int arr[10];
    for(int j = 0; j < string_length; j++) {
      arr[j] = strings_count(words, allLenght, tmp[j]);
    }
    if(ints_min(arr, string_length) == 1)
      unique[result++] = str[i];
  }
  return result;
}

int finalChar(const char **unique, int length, const char **words,
                              int allLenght, const char **final) {
  int result = 0;
  for(int i = 0; i < length; i++) {
    final[result++] = unique[i];
    const char *tmp[MAX];
    int string_length = string_split(unique[i], tmp);
    for(int j = 0; j < string_length; j++) {
      if(strings_count(words, allLenght, tmp[j]) == 1)
        final[result++] = tmp[j];
    }
  }
  return result;
}


void camoes() {
  const char *input[MAX];
  int length = strings_read(stdin, input);
  const char *words[MAX];
  int allLength = allWords(input, length, words);
  const char *unique[MAX];
  int uniqueLength = names_with_unique_words(input, length, words, allLength, unique);
  const char *final[MAX];
  int finalLength = finalChar(unique, uniqueLength, words, allLength, final);
  if(finalLength < 1)
    printf("***\n");
  else
    strings_fprint_basic(stdout, final, finalLength);
}

/*----------------------------------------------------------------------------------- B --------------------------------------------------------------------------------*/

typedef struct {
  const char *name;
  int date;
} NomeAno;

NomeAno infos(const char *name, int date) {
  NomeAno result;
  result.name = name;
  result.date = date;
  return result;
}

char *substring_byComa(const char *str, char *tmp) {
  int i = 0, j = 0;
  while(str[i] != ',' && str[i] != '\0')
    tmp[j++] = str[i++];
  tmp[j] = '\0';
  return tmp;
}

int comaIdx(const char *str) {
  int i = 0, idx = 0;
  while(str[i] != '\0') {
    if(str[i] == ',')
      idx = i+1;
    i++;
  }
  return idx;
} 
/*
void getNames(const char **str, int length, const char **name) {
  for(int i = 0; i < length; i++) {
    char tmp[100];
    substring_byComa(str[i], tmp);
    name[i] = str_dup(tmp);
  }
}

void getDate(const char **str, int length, int *arr) {
  for(int i = 0; i < length; i++) {
    char tmp[100];
    int coma = comaIdx(str[i]);
    word(str[i]+coma, tmp);
    arr[i] = atoi(tmp);
  }
}*/

int fillStruct(const char **str, int length, NomeAno *info) {
  int result = 0;
  for(int i = 0; i < length; i++) {
    char tmpn[100];
    substring_byComa(str[i], tmpn);
    char tmpd[100];
    int coma = comaIdx(str[i]);
    word(str[i]+coma, tmpd);
    int num = atoi(tmpd);
    info[result++] = infos(str_dup(tmpn), num);
  }
  return result;
}

int getYear(int num) {
  return num / 10000;
}

int getMD(int num) {
  return num - getYear(num)*10000;
}



void exchange(NomeAno *info, int i, int j) {
  NomeAno tmp = info[i];
  info[i] = info[j];
  info[j] = tmp;
}

int cmp(NomeAno *info, int i , int j) {
  int result = getMD(info[i].date) - getMD(info[j].date);
  if(result == 0) 
    result = strcmp(info[i].name, info[j].name);
  return result;
}

void sort(NomeAno *info, int length) {
  for(int i = 1; i < length; i++) {
    int j = i;
    while(j > 0 && cmp(info, j-1, j) > 0) {
      exchange(info, j-1, j);
      j--;
    }
  }
}

int find(NomeAno *info, int length, int day) {
  int i = 0;
  while(((getMD(day) - getMD(info[i].date)) > 0) && (i < length))
    i++;
  return i;
}

void rotateStruct(NomeAno *info, int length, int day, NomeAno *final) {
  int result = 0;
  int x = find(info, length, day);
  //printf("%d\n", x);
  for(int i = x; i < length; i++)
    final[result++] = infos(info[i].name, info[i].date);

  for(int j = 0; j < x; j++) 
    final[result++] = infos(info[j].name, info[j].date);
}

void changeYear(NomeAno *final, int length, int day) {
  int base = getMD(day);
  int baseYear = getYear(day);
  for(int i = 0; i < length; i++) {
    if(getMD(final[i].date) >= base) {
      int x = (baseYear * 10000) + getMD(final[i].date);
      final[i].date = x;
    }
    if(getMD(final[i].date) <  base){
      int x = ((baseYear+1) * 10000) + getMD(final[i].date);
      final[i].date = x;
    }
  }
}


void printStruct(NomeAno *info, int length) {
  for(int i = 0; i < length; i++)
    printf("%s %d\n", info[i].name, info[i].date);
}

void aniversarios(const char *filename) {
  FILE *f = fopen(filename, "r");
  const char *input[MAX];
  int length = strings_read(f, input);
  NomeAno info[MAX];
  int structLength = fillStruct(input, length, info);
  sort(info, structLength);
  //printStruct(info, structLength);
  int day;
  while(scanf("%d", &day) != EOF) {
    NomeAno final[MAX];
    rotateStruct(info, structLength, day, final);
    changeYear(final, structLength, day);
    printStruct(final, structLength);
  }
}

/*----------------------------------------------------------------------------------- C --------------------------------------------------------------------------------*/

char *message[2] = {"NO", "YES"};

typedef struct {
  int day;
  double incidence;
  double transmissibility;
} Covid;

Covid covids(int day, double incidence, double transmissibility) {
  Covid result;
  result.day = day;
  result.incidence = incidence;
  result.transmissibility = transmissibility;
  return result;
}

int covid_read(FILE *f, Covid *covid) {
  int result = 0;
  int day;
  double incidence;
  double transmissibility;
  while(fscanf(f, "%d%lf%lf", &day, &incidence, &transmissibility) != EOF)
    covid[result++] = covids(day, incidence, transmissibility);
  return result;
}

typedef struct {
  int days;
  int state;
} UpsDowns;

UpsDowns variations(int days, int state) {
  UpsDowns result;
  result.days = days;
  result.state = state;
  return result;
}

int checkSate(Covid *covid, int i , int j) {
  if(covid[i].incidence < covid[j].incidence || covid[i].transmissibility < covid[j].transmissibility)
    return -1;
  return 0;
}

int getUpsDowns(Covid *covid, int length, UpsDowns *variation) {
  int result = 0;
  for(int i = 1; i < length; i++) {
    int days = covid[i].day - covid[i-1].day;
    int var = checkSate(covid, i-1, i);
    variation[result++] = variations(days, var);
  }
  return result;
}

int count_while_idx(UpsDowns *variation, int length, int var, int idx) {
  int result = 0, i = idx;
  while(variation[i].state == var && i < length) {
    result++;
    i++;
  }
  return result;
}

int count_while_days(UpsDowns *variation, int length, int var, int idx) {
  int result = 0, i = idx;
  while(variation[i].state == var && i < length) {
    result += variation[i].days;
    i++;
  }
  return result;  
}

int getFinalStruct(UpsDowns *variation, int length, UpsDowns *final) {
  int i = 0, result = 0;
  while(i < length) {
    int d = count_while_days(variation, length, variation[i].state ,i);
    int idx = count_while_idx(variation, length, variation[i].state ,i);
    //printf("%d %d\n", d, idx);
    final[result++] = variations(d, variation[i].state);
    i += idx;
  }
  return result;
}

int getMaxDays(UpsDowns *variation, int length, int var) {
  int check = 0;
  for(int i = 0; i < length; i++) {
    if(variation[i].state == var && variation[i].days > check)
      check = variation[i].days;
  }
  return check;
}

int getMessage(UpsDowns *variation, int length) {
  int down = getMaxDays(variation, length, -1);
  int up = getMaxDays(variation, length, 0);
  if(up >= down)
    return 1;
  return 0;
}

/*void printc(UpsDowns *variation, int length) {
  for(int i = 0; i < length; i++) {
    printf("%d %d \n", variation[i].days, variation[i].state);
  }
}*/

void oXisdoCosta() {
  Covid covid[MAX];
  int length = covid_read(stdin, covid);

  UpsDowns variation[MAX];
  int udLength = getUpsDowns(covid, length, variation);
  //printc(variation, udLength);
  //printf("\n");

  /**** WORKS TILL HERE ****/

  UpsDowns final[MAX];
  int finalength = getFinalStruct(variation, udLength, final);
  //printc(final, finalength);
  //printf("\n");

  int idxMessage = getMessage(final, finalength);
  printf("%s\n", message[idxMessage]);
}

/*--------------------------------------------------------------------------------- Main -------------------------------------------------------------------------------*/

int main(int argc, char **argv) {
  int x = 'A';
  if(argc > 1)
    x = *argv[1];
  if(x == 'A')
  camoes();
  else if(x == 'B')
    aniversarios(argv[2]);
  else if(x == 'C')
    oXisdoCosta();
  else if("All unit tests PASSED.\n")
  return 0;
}