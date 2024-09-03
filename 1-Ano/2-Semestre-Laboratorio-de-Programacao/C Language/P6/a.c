#include<stdio.h>
#include<math.h>
#include<string.h>

#include"our_ints.h"
#include"our_doubles.h"

// Set all elements to zero
void doubles_clear(double *a, int n)
{
  memset(a, 0, (size_t)n * sizeof(double));
}

// Set all elements to zero
void matrix_clear(int r, int c, double m[r][c])
{
  doubles_clear((double *)m, r*c);
}


/************************************* A **********************************/

void get_system(int r, double matrix[r][r+1]) {
  doubles_get_some((double *) matrix, r*(r+1));
}

void print_system(int r, const double matrix[r][r+1]) {
  for(int i = 0; i < r; i++)
    doubles_printfln("%12f", matrix[i], r+1);
}

void ler_sistema() {
  int num_rows;
  scanf("%d", &num_rows);
  double matrix[num_rows][num_rows+1];
  get_system(num_rows, matrix);
  print_system(num_rows, matrix);
}

/************************************* B **********************************/

// put last colum = solutions in an array 
void get_solutions(int r, double matrix[r][r+1], double *solution) {
  for(int i = 0; i < r; i++)
    solution[i] = matrix[i][r];
}

// Multiply the possible solutions by a collum
void mult_collum(int r, double matrix[r][r+1], double m[r][r+1], int idx, double var) {
  for(int i = 0; i < r; i++)
    m[i][idx] = matrix[i][idx] * var;
}

// Use mult_collum to multiply every collum by the possible solutions
void get_collum_var(int r, double matrix[r][r+1], double m[r][r+1],  double *arr) {
  for(int i = 0; i < r; i++) 
    mult_collum(r, matrix, m, i, arr[i]);
}

// Summ a row
double row_sum(int r, double matrix[r][r+1], int idx) {
  double result = 0.0;
  for(int i = 0; i < r; i++) {
    result += matrix[idx][i];
  }
  return result;
}

// Uses the row_sum to get all sum of all collums execpt the last
// And puts those values in a array for easy comparation
void solution_arr(int r, double matrix[r][r+1], double *arr) {
  for(int i = 0; i < r; i++) 
    arr[i] = row_sum(r, matrix, i);
}

// Check if the possible solutions are actualy solutions
int check_solution(int r,double matrix[r][r+r], double *arr) {
  double s[r];
  get_solutions(r, matrix, s);
  double tmp[r];
  for(int i = 0; i < r; i++) {
    double m[r][r+1];
    matrix_clear(r, r+1, m);
    get_collum_var(r, matrix, m, arr);
    solution_arr(r, m, tmp);
  }
  return doubles_equal(tmp, r, s, r);
}

// Builds array with 0 if not solutions and 1 if solution
int is_solution(int r, double matrix[r][r+1], double *arr, int length, int *final) {
  int result = 0;
  for(int i = 0; i < length; i += r) {
    int check = check_solution(r, matrix, arr+i);
    final[result++] = check;
  }
  return result;
}

// Print array positions in each line
void print_solutions_test(int *arr, int length) {
  for(int i = 0; i < length; i++)
    printf("%d\n", arr[i]);
}

void verificar_solucao() {
  int num_rows;
  scanf("%d", &num_rows);
  double matrix[num_rows][num_rows+1];
  double arr[1000];
  get_system(num_rows, matrix);
  int length = doubles_get(arr);
  int final[1000];
  int finalength = is_solution(num_rows, matrix, arr, length, final);
  print_solutions_test(final, finalength);
}

/************************************* C **********************************/

//
void next_solution_test(double *arr, int n, int max)
{
  int i = 0;
  if (arr[i] < max || n == 1)
  {
    arr[i] += 1;
  }
  else
  {
    arr[i] = (-1)*max;
    next_solution_test(arr+1, n-1, max);
  }
}


int brute_force(double *arr, int n, double matrix[n][n+1], int max) {
  while (arr[n-1] <= max) {
    int var = check_solution(n, matrix, arr);
    if (var)
      return var;
    else 
      next_solution_test(arr, n, max);
  }
  return 0;
}

void resolver_forca_bruta() {
  int n;
  scanf("%d", &n);
  double matrix[n][n+1];
  get_system(n, matrix);
  int max;
  scanf("%d", &max);

  double arr[n];
  doubles_fill((-1)*max, n, arr);
  
  int var = brute_force(arr, n, matrix, max);
  if (var)
    doubles_println(arr, n, " ");
  else 
    printf("***\n");
}

/************************************* D **********************************/

void column_to_array(int n, double matrix[n][n+1], int idx, double *arr) {
  for(int i = 0; i < n; i++) 
    arr[i] = matrix[i][idx];
}

void row_divison(int n, double matrix[n][n+1], int idx, double var) {
  for(int i = 0; i < n+1; i++)
    matrix[idx][i] = matrix[idx][i] / var;
}

void columnize(int n, double a[n][n+1], int x) {
  double arr[n];
  column_to_array(n, a, x, arr);
  for(int i = 0; i < n; i++) {
    if(arr[i] != 0)
      row_divison(n, a, i, arr[i]);
  }
}

void row_subtract(int n, double matrix[n][n+1], int idx, int x) {
  for(int i = 0; i < n+1; i++)
    matrix[idx][i] = matrix[idx][i] - matrix[x][i];
}

void subtract_row(int n, double a[n][n+1], int x) {
  for(int i = 0; i < n; i++) {
    if(i != x && a[i][x] != 0 && a[x][x] != 0)
      row_subtract(n, a, i, x);
  }
}

int set_solution(int n, double matrix[n][n+1]) {
  for(int i = 0; i < n; i++) {
    if(matrix[i][i] != 1)
      return 0;
  }
  return 1;
}

int diagonal(int n, double matrix[n][n+1], int idx) {
  for(int i = 0; i < n; i++) 
    if((i != idx && matrix[idx][i] != 0) || (i == idx && matrix[idx][i] == 0))
      return 0;
  return 1; 
}

int verification_diagonal(int n, double matrix[n][n+1]) {
  for(int i = 0; i < n; i++) {
    int var = diagonal(n, matrix, i);
    if(var == 0)
      return 0;
  }
  return 1;
}

void solve(int n, double matrix[n][n+1], double *arr) {
  int count = 0, i = 0;
  while(i < n) {
    columnize(n, matrix, i);
    subtract_row(n, matrix, i);
    count++;
    if(set_solution(n, matrix) == 1) {
      column_to_array(n, matrix, n, arr);
      return;
    } 
    else if(verification_diagonal(n, matrix) == 1 && count >= n)
      i--;
    else
      i++;
  }
}

void gauss() {
  int n;
  scanf("%d", &n);
  double matrix[n][n+1];
  get_system(n, matrix);
  double arr[n];
  solve(n, matrix, arr);
  doubles_println(arr, n, " ");
}

/************************************* E **********************************/


void row_to_array(int n, double matrix[n][n+1], int idx, double *arr) {
  for(int i = 0; i < n; i++)
    arr[i] = matrix[idx][i];
}

int null_line(int n, double matrix[n][n+1]) {
  double arr[n];
  for(int i = 0; i < n; i++) {
    row_to_array(n, matrix, i, arr);
    if(doubles_min(arr, n) == 0 && doubles_max(arr, n) == 0)
      return 1;
  }
  return 0;
}

void verification_epsilon(int n, double matrix[n][n+1], int idx, double epsilon) {
  for(int i = 0; i < n; i++) {
    double var = round(matrix[idx][i]);
    double var2 = fabs(var - matrix[idx][i]);
    if(var2 <= epsilon)
      matrix[idx][i] = var;
  }
}

void epsilon_(int n, double matrix[n][n+1], double epsilon) {
  for(int i = 0; i < n; i++)
    verification_epsilon(n+1, matrix, i, epsilon);
}

void switch_row(int n, double matrix[n][n+1], int idx) {
  int i = 0;
  while((matrix[idx][idx] == 0) && (i < n)) {
    if(idx != i)
      doubles_exchange(*matrix, i, idx);
    i++;
  }
}

int impossible_system(int n, double matrix[n][n+1]) {
  for(int i = 0; i < n; i++)
	  if(matrix[i][i] == 0 && verification_diagonal(n, matrix))
      return 1;
  return 0;
}

int gauss_epsilon(int n, double matrix[n][n+1], double *arr) {
  int i = 0;
  while(i < n) {
    switch_row(n, matrix, i);

    //print_system(n,matrix);
    //printf("\n");

    columnize(n, matrix, i);

    //print_system(n,matrix);
    //printf("\n");

    subtract_row(n, matrix, i);

    //print_system(n,matrix);
    //printf("\n");

    epsilon_(n, matrix, 10e-13);

    //print_system(n,matrix);
    //printf("\n");

    if(set_solution(n, matrix)) {
      column_to_array(n, matrix, n, arr);
      return 1;
    }
    
		else if(impossible_system(n, matrix) || null_line(n, matrix))
      return 0;

    else if(i == n-1)
      i = 0;
    
		else
  	  i++;
  }
  return 0;
}

void gauss_completo() {
  int n;
  scanf("%d", &n);
  double matrix[n][n+1];
  get_system(n, matrix);

  double arr[n];
  int var = gauss_epsilon(n, matrix, arr);
  if(var)
    doubles_println(arr, n, " ");
  else
    printf("System is impossible or indeterminate. Computation halted.\n");
}

/*********************************** Main**********************************/

int main(int argc, char **argv) {
  int x = 'A';
  if(argc > 1)
    x = *argv[1];
  if(x == 'A')
    ler_sistema();
  else if(x == 'B')
    verificar_solucao();
  else if(x == 'C')
    resolver_forca_bruta();
  else if(x == 'D')
    gauss();
  else if(x == 'E')
    gauss_completo();
  else if("All unit tests PASSED.\n")
  return 0;
}