int str_len(const char *s)
{
  int result = 0;
  while (s[result] != '\0')
    result++;
  return result;
}


// Copy `s` to `r`, return `r`.
// `r` should not overlap `s` to the right.
char* str_cpy(char *r, const char *s)
{
  int n = 0;
  for (int i = 0; s[i]; i++)
    r[n++] = s[i];
  r[n] = '\0';
  return r;
}

// Are the two strings equal?
int str_equal(const char *s, const char *t)
{
  int i = 0;
  while (s[i] && t[i] && s[i] == t[i])
    i++;
  return s[i] == '\0' && t[i] == '\0';
}

int str_find(const char *s, char x)
{
  for (int i = 0; s[i] != '\0'; i++)
    if (s[i] == x)
      return i;
  return -1;
}


// Read a line from `f` to `s`. Does not control buffer overflow.
int str_readline(FILE *f, char *s)
{
  int result = EOF;
  char *p = fgets(s, INT_MAX, f);
  if (p != NULL)
  {
    result = str_len(s);
    if (result > 0 && s[result-1] == '\n')
      s[--result] = '\0';
  }
  return result;
}

// Create a dynamic copy of `s` and return its address
const char *str_dup(const char *s)
{
  char *result = (char *) malloc(strlen(s) + 1);
  strcpy(result, s);
  return result;
}

// Create a dynamic copy of at most the first `n` bytes of `s`
// and return its address
const char *str_ndup(const char *s, int n)
{
  char *result = (char *) malloc(n + 1);
  str_ncpy(result, s, n);
  result[n] = '\0';
  return result;
}

int str_count_while(const char *s, char x)
{
  int result = 0;
  while (s[result] != '\0' && s[result] == x)
    result++;
  return result;
}

int str_count_while_not(const char *s, char x)
{
  int result = 0;
  while (s[result] != '\0' && s[result] != x)
    result++;
  return result;
}

int str_count_while_not_func(const char *s, int f(int))
{
  int result = 0;
  while (s[result] != '\0' && !f(s[result]))
    result++;
  return result;
}

int str_count_while_is_not_space(const char *s)
{
  int result = 0;
  while (s[result] != '\0' && !isspace(s[result]))
    result++;
  return result;
}

// --------

void strings_fprint_basic(FILE *f, const char **a, int n)
{
  for (int i = 0; i < n; i++)
    fprintf(f, "%s\n", a[i]);
}

void strings_fprint(FILE *f, const char **s, int n, const char *separator)
{
  if (n > 0)
  {
    fprintf(f, "%s", s[0]);
    for (int i = 1; i < n; i++)  // i = 1
      fprintf(f, "%s%s", separator, s[i]);
  }
}

void strings_fprintln(FILE *f, const char **s, int n, const char *separator)
{
  strings_fprint(f, s, n, separator);
  fprintf(f, "\n");
}

void strings_print(const char **s, int n, const char *separator)
{
  strings_fprint(stdout, s, n, separator);
}

void strings_println(const char **s, int n, const char *separator)
{
  strings_fprintln(stdout, s, n, separator);
}

void strings_fprintf(FILE *f, const char **s, int n, const char *fmt)
{
  for (int i = 0; i < n; i++)
    fprintf(f, fmt, s[i]);
}

void strings_fprintfln(FILE *f, const char **s, int n, const char *fmt)
{
  strings_fprintf(f, s, n, fmt);
  fprintf(f, "\n");
}

void strings_printf(const char **s, int n, const char *fmt)
{
  strings_fprintf(stdout, s, n, fmt);
}

void strings_printfln(const char **s, int n, const char *fmt)
{
  strings_fprintfln(stdout, s, n, fmt);
}

int strings_read(FILE *f, const char **a)
{
  int result = 0;
  char line[max_line_length];
  while (str_readline(f, line) != EOF)
    a[result++] = str_dup(line);
  return result;
}

void test_read_write(void)
{
  const char *a[1000];
  int n = strings_read(stdin, a);
  strings_fprint_basic(stdout, a, n);
}

// --------

// New stuff

// Read a file into a single string
char *str_from_file(char *r, FILE *f)
{
  int n = 0;
  char x;
  while (fscanf(f, "%c", &x) != EOF)
    r[n++] = x;
  r[n] = '\0';
  return r;
}

void test_str_from_file(void)
{
//  char s[1000];
  char s[400000];
  str_from_file(s, stdin);
  printf("%d\n", str_len(s));
  printf("<%s>\n", s);
}

// Splitting a string into lines
// Not a good technique here, because if the string changes, the lines
// will also change, and that's not what we want, in general.
int str_lines0(char *s, const char **a)
{
  int result = 0;
  int i = 0;
  while (s[i])
  {
    a[result++] = s+i;
    int z = str_count_while_not(s+i, '\n');
    i += z;
    if (s[i] != '\0') // if not at the end of string, replace '\n' by '\0'
      s[i++] = '\0';
  }
  return result;
}

// Splitting a string into lines
int str_lines(const char *s, const char **a)
{
  int result = 0;
  int i = 0;
  while (s[i])
  {
    int z = str_count_while_not(s+i, '\n');
    a[result++] = str_ndup(s+i, z);
    i += z;
    if (s[i]) // if not at the end of strings, skip the `'\0'`.
      i++;
  }
  return result;
}

void test_str_lines(void)
{
  char s[400000];
  str_from_file(s, stdin);
  printf("<%s>\n", s);
  const char *a[10000];
  int n = str_lines(s, a);
  strings_fprintf(stdout, a, n, "[%s]\n");
}

// Splitting a string into words
// Not a good idea again, because if the string changes, the words will also
// change, and that's not what we want, in general.
int str_words0(char *s, const char **a)
{
  int result = 0;
  int i = 0;
  while (s[i])
    if (isspace(s[i]))
      i++;
    else
    {
      a[result++] = s+i;
      int z = str_count_while_is_not_space(s+i);
      i += z;
      if (s[i] != '\0')
        s[i++] = '\0';
    }
  return result;
}

// Splitting a string into words
int str_words(const char *s, const char **a)
{
  int result = 0;
  int i = 0;
  while (s[i])
    if (isspace(s[i]))
      i++;
    else
    {
      int z = str_count_while_not_func(s+i, isspace);
      a[result++] = str_ndup(s+i, z);
      i += z;
    }
  return result;
}

void test_str_words(void)
{
  char s[400000];
  str_from_file(s, stdin);
  const char *a[100000];
  int n = str_words(s, a);
  strings_printf(a, n, "{%s}\n");
}

void test_str_words_again(void)
{
  char s[1000];
  str_readline(stdin, s);
  const char *a[100];
  int n = str_words(s, a);
  strings_printf(a, n, "{%s}\n");
  str_readline(stdin, s);
  strings_printf(a, n, "{%s}\n");
}

int str_count(const char *s, char x)
{
  int result = 0;
  for (int i = 0; s[i]; i++)
    if (s[i] == x)
      result++;
  return result;
}
                            
int str_count_words(const char *s)
{
  int result = 0;
  int i = 0;
  while (s[i])
    if (isspace(s[i]))
      i++;
    else
    {
      int z = str_count_while_is_not_space(s+i);
      result++;
      i += z;
    }
  return result;
}
