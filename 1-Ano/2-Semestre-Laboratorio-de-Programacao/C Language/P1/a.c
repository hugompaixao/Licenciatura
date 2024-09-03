#include<stdio.h>
#include<assert.h>
#include"our_ints.h"
#include"our_doubles.h"
#define CONSOLE "CON"



// Maiores Divisores Impares --------------------------------------------------------------------------------------------------------------------------------

int maxDivisoresImpar(int num) {
    while(num % 2 == 0) 
    	num = num / 2;
    return num;
}

int maxDivisorImpar(int *arr, int length, int *arrTmp) {
	int result = 0;
	for(int i = 0; i < length; i++) 
		arrTmp[result++] = maxDivisoresImpar(arr[i]);
	assert(length == result);
	return result;
}

void maioresDivisoresImpares() {
	int arr[1000];
	int length = ints_get(arr);
	int arrTmp[1000];
	int lengthTmp = maxDivisorImpar(arr, length, arrTmp);
	ints_println_basic(arrTmp, lengthTmp);
}

// Variaçoes Relativas -------------------------------------------------------------------------------------------------------------------------------------

double variacao(double x, double y) {
	return (x-y) / y;
}

int variacoes(double *arr, int length, double *arrTmp) {
	int result = 0;
	for(int i = 1; i < length; i++)
		arrTmp[result++] = variacao(arr[i], arr[i-1]);
	return result;
}

void variacoesRelativas() {
	double arr[1000];
	int length = doubles_get(arr);
	double arrTmp[1000];
	int lengthTmp = variacoes(arr, length, arrTmp);
	double maxVariacao = doubles_max(arrTmp, lengthTmp);
	printf("%f\n", maxVariacao);
}

// Pingao --------------------------------------------------------------------------------------------------------------------------------------------------

int somaFinalCompras(int *arr, int length, int *arrTmp) {
	int idx = 0;
	int soma = 0;
	for(int i = 1; i < length; i++) {
		soma += arr[i];
		if(soma >= arr[0]) {
			arrTmp[idx++] = soma;
			soma = 0;
		}
	}
	return idx;	
}

int bilhetesCinema(int *arr, int length, int valor) {
	int numeroBilhetes = 0;
	for(int i = 0; i < length; i++) {
		numeroBilhetes += (arr[i] / valor);
	}
	return numeroBilhetes;
}

void pingao() {
	int arr[1000];
	int length = ints_get(arr);

	int arrTmp[1000];
	int lengthTmp = somaFinalCompras(arr, length, arrTmp);

	int bilhetes = bilhetesCinema(arrTmp, lengthTmp, arr[0]);
	printf("%d\n", bilhetes);
}

// Oceano --------------------------------------------------------------------------------------------------------------------------------------------------

int todasPossiblidadesProdutos(int *arr, int length, int valorPagar, int *arrTmp) {
	int idx = 0;
	for(int i = 1; i < length; i++) {
		if(valorPagar + arr[i] >= arr[0]) {
			arrTmp[idx++] = arr[i]; 
		}
	}
	return idx;
}

int produtoNecessario(int *arr, int length) {
	if(length < 1)
		return 0;
	return ints_min(arr, length);
}

void oceano() {
	int arr[1000];
	int length = ints_get(arr);

	int valorPagar = ints_sum(arr, length) - arr[0];
	int arrTmp[1000];
	int lengthTmp = todasPossiblidadesProdutos(arr, length, valorPagar, arrTmp);

	int produto = produtoNecessario(arrTmp, lengthTmp);
	printf("%d\n", produto);	
}

// Bolsa ---------------------------------------------------------------------------------------------------------------------------------------------------

char *message[2] = {"NO", "YES"};


int contarAscendentes(double *arr, int length, int i) {
	int result = 0;
	while(i < length && arr[i] > arr[i-1]) {
		result++;
		i++;
	} 
	return result;
}

int arrayAscendentes(double *arr, int length) {
	int arrTmp[1000];
	int idx = 0;
	int i = 1;
	while(i < length) {
		if(arr[i] > arr[i-1]) {
			int tmp = contarAscendentes(arr, length, i);
			arrTmp[idx++] = tmp;
			i += tmp;
		}
		i++;
	}
	if(arrTmp[idx-1] >= ints_max(arrTmp, idx)) 
		return 1;
	return 0;	
}

int verificarHoje(double *arr, int length) {
	if(arr[length-1] <= arr[length-2])
		return 0;
	return arrayAscendentes(arr, length);
}

void bolsa() {
	double arr[1000];
	int length = doubles_get(arr);
	assert(length > 1 || length <= 1000);
	int idx = verificarHoje(arr, length);
	printf("%s", message[idx]);
}

// Main ---------------------------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char **argv) {
	int x = 'A';
	if(argc > 1)
		x = *argv[1];
	if(x == 'A'){
		maioresDivisoresImpares();
	} else if(x == 'B') {
		variacoesRelativas();
	} else if(x == 'C') {
		pingao(); 
	} else if(x == 'D') {
		oceano(); 
	} else if(x == 'E') {
		bolsa();
	} else if("All unit tests PASSED.\n ")
	return 0;
}