#include<stdio.h>
#include<string.h>
#include<limits.h>
#include<stdlib.h>

#define MAX 100000

// Strings Read

int str_len(const char *str) {
	int result = 0;
	while(str[result] != '\0')
		result++;
	return result;
}

const char *str_dup(const char *str) {
	char *result = (char *) malloc(strlen(str) + 1);
	strcpy(result, str);
	return result;
}

int str_readline(FILE *f, char *str) {
	int result = EOF;
	char *p = fgets(str, MAX, f);
	if(p != NULL) {
		result = str_len(str);
		if(result > 0 && str[result-1] == '\n')
			str[--result] = '\0';
	}
	return result;
}

int strings_read(FILE *f, const char **str) {
	int result = 0;
	char line[MAX];
	while(str_readline(f, line) != EOF)
		str[result++] = str_dup(line);
	return result;
}

// Strings Print

void strings_fprint_basic(FILE *f, const char **str, int length) {
	for(int i = 0; i < length; i++) {
		fprintf(f, "%s\n", str[i]);
	}
}

//------------------------------------------------------------------

// Funcoes Strings

char* first_name(const char *str, char * strTmp) {
  int i = 0, j = 0;
  while(str[i] != ' ') 
    strTmp[j++] = str[i++];
  strTmp[j] = '\0';
  return strTmp;
}

int strings_count_while(const char **str, int length, const char *string) {
  int result = 0;
  while(result < length && strcmp(str[result], string) == 0)
    result++;
  return result;
}

void strings_exchange(const char **str, int i, int j) {
  const char *strTmp = str[i];
  str[i] = str[j];
  str[j] = strTmp;
}

void strings_isort(const char **str, int length) {
  for(int i = 1; i < length; i++) {
    int j = i;
    while(j > 0 && strcmp(str[j-1], str[j]) > 0) {
      strings_exchange(str, j-1, j);
      j--;
    }
  }
}

void strings_isort_two(const char **str, const char **newstr, int length) {
  for(int i = 1; i < length; i++) {
    int j = i;
    while(j > 0 && strcmp(str[j-1], str[j]) > 0) {
      strings_exchange(str, j-1, j);
      strings_exchange(newstr, j-1, j);
      j--;
    }
  }
}

//------------------------------------------------------------------------ A

int strings_unique(const char **str, int length, const char **strNew) {
  int result = 0, i = 0;
  while(i < length) {
    int z = strings_count_while(str+i, length-i, str[i]);
    strNew[result++] = str[i];
    i += z;
  }
  return result;
}

int unique_first_names(const char **str, int length, const char **strNew) {
  const char *constStrTmp[MAX];
  char strTmp[MAX]; 
  for(int i = 0; i < length; i++) {
    first_name(str[i], strTmp);
    constStrTmp[i] = str_dup(strTmp);
  }
  return strings_unique(constStrTmp, length, strNew);
}

void nomes_proprios() {
  const char *str[MAX];
  int length = strings_read(stdin, str);
  const char *str_out[MAX]; 
  int final_length = unique_first_names(str, length, str_out);
 strings_fprint_basic(stdout, str_out, final_length);
}

//------------------------------------------------------------------------ B

typedef struct {
  const char *string;
  int number;
} StringInt;

//  inicialização do struct
StringInt string_int(const char *string, int number) {
  StringInt result;
  result.string = string;
  result.number = number;
  return result;
}

// print da struct
void string_ints_print(const StringInt *strInt, int length) {
  for(int i = 0; i < length; i++) {
    printf("%s %d\n", strInt[i].string, strInt[i].number);
  }
}

// recebe Strings coloca na strut o nome e as vezes que este aparece
int strings_tally(const char **str, int length, StringInt *strInt) {
  int result = 0, i = 0;
  while(i < length) {
    int count = strings_count_while(str+i, length-i, str[i]);
    strInt[result].string = str[i];
    strInt[result++].number = count;
    i += count;
  }
  return result;
}

void exchange(StringInt *strInt, int i, int j) {
  StringInt strIntTmp = strInt[i];
  strInt[i] = strInt[j];
  strInt[j] = strIntTmp;
}

// Ordenar forma decrescente
void strings_ints_isort(StringInt *strInt, int length) {
  for(int i = 1; i < length; i++) {
    int j = i;
    while(j > 0 && strInt[j-1].number < strInt[j].number) {
      exchange(strInt, j-1, j);
      j--;
    }
  }
}

// forma nova String com apenas nome proprio
void first_name_string(const char **str, int length, const char **newStr) {
  for(int i = 0; i < length; i++) {
    char strTmp[MAX];
    first_name(str[i], strTmp);
    newStr[i] = str_dup(strTmp);
  }
}

void ranking_nomes_proprios() {
  const char *str[MAX];
  int length = strings_read(stdin, str);
  const char * str_1_name[MAX];
  StringInt strInt[MAX];
  first_name_string(str, length, str_1_name);
  strings_isort(str_1_name, length);
  int new_length = strings_tally(str_1_name, length, strInt);
  strings_ints_isort(strInt, new_length);
  string_ints_print(strInt, new_length);
}

//------------------------------------------------------------------------ C

int get_index(const char *str){
  int length = str_len(str);
  //printf("%d\n", length);
  int i = 0, index;
  while(length > i && str[length] != ' ') {
    index = length;
    length--;
  }
  return index;
}

int last_name_cmp(const char* str, const char* str2) {
  int result = strcmp(str+get_index(str), str2+get_index(str2));
  if (result == 0)
    result = strcmp(str, str2);
  return result;
}

void last_names_isort(const char **str, int length) {
  for (int i = 1; i < length; i++) {
    int j = i;
    while (j > 0 && last_name_cmp(str[j-1],str[j]) > 0) {
      strings_exchange(str, j-1, j);
      j--;
    }
  }
}

void listagem_nomes_por_apelido() {
  const char *str[MAX];
  int length = strings_read(stdin, str);
  last_names_isort(str, length);
  strings_fprint_basic(stdout, str, length);
}

//------------------------------------------------------------------------ D

typedef struct {
  const char *_1;
  const char *_2;
} StringString;

StringString string_string(const char *_1, const char *_2) {
  StringString result;
  result._1 = _1;
  result._2 = _2;
  return result;
}

void fill_struct(StringString *strings, int length, const char **strF, const char **strA) {
  for(int i = 0; i < length; i++) {
    strings[i] = string_string(strF[i], strA[i]);
  }
}

char *getlast_name(const char *str, char *strLName) {
  int j = 0;
  int idx = get_index(str);
  while(str[idx] != '\0')
    strLName[j++] = str[idx++];
  strLName[j] = '\0';
  return strLName;
}

void last_name(const char **str, int length, const char **newstr) {
  int result = 0;
  for(int i = 0; i < length; i++) {
    char tmp[MAX];
    getlast_name(str[i], tmp);
    newstr[result++] = str_dup(tmp);
  }
}

void string_string_exchange(StringString *strings, int i, int j) {
StringString tmp_strings = strings[i];
  strings[i] = strings[j];
  strings[j] = tmp_strings;
}

int String_cmp(StringString string1, StringString string2) {
  int result = strcmp(string1._2, string2._2);
  if(result == 0)
    result = strcmp(string1._1, string2._1);
  return result;
}

void String_last_name_isort(StringString *strings, int length) {
  for (int i = 1; i < length; i++) {
    int j = i;
    while (j > 0 && String_cmp(strings[j-1],strings[j]) > 0) {
      string_string_exchange(strings, j-1, j);
      j--;
    }
  }
}


void print_StringString(StringString *strings, int length) {
  for(int i = 0; i < length; i++) {
    printf("%s\n", strings[i]._1);
  }
}

void listagem_nomes_por_apelidos_V2() {
  const char *str[MAX];
  int length = strings_read(stdin, str);
  const char *str_last_name[MAX];
  StringString strings[MAX];
  last_name(str, length, str_last_name);
  //strings_fprint_basic(stdout, str_last_name, length);
  //printf("\n");
  fill_struct(strings, length, str, str_last_name);
  String_last_name_isort(strings, length);
  print_StringString(strings, length);
}

int main(int argc, char **argv) {
    int x = 'A';
    if(argc > 1)
        x = *argv[1];
    if(x == 'A') {
        nomes_proprios();
    } else if(x == 'B') {
        ranking_nomes_proprios();
    } else if(x == 'C') {
        listagem_nomes_por_apelido();
    } else if(x == 'D') {
        listagem_nomes_por_apelidos_V2(); 
    } else if("All unit tests PASSED.\n")
    return 0;
}