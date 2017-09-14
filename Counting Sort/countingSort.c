#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int CountLine(char *nameTxt){
	char caracter;
	char number[20];
	int numLine = 0;

	FILE *arq;
	
	arq = fopen(nameTxt, "r");

	if(arq == NULL)
		printf("Erro ao abrir o arquivo\n");

	while(!feof(arq)){
		caracter = fgetc(arq);
		if(caracter == '\n' || feof(arq))
			numLine++;
	}

	fclose(arq);
	
	return numLine;
}

void FillArray(int *A, char *nameTxt){
	FILE *arq;
	char number[20];
	int i = 0;

	arq = fopen(nameTxt, "r");

	if(arq == NULL)
		printf("Erro ao abrir o arquivo\n");
	
	while(!feof(arq)){
		fgets(number, 20, arq);
		A[i] = atoi(number);
		i++;
	}
		
	fclose(arq);
}

void CountingSort(int *A, int *B, int k, int sizeA){
	int i, j;
	int neg = 0;
	int neg1 = 0;

	for(i = 0; i < sizeA; i++){
		if(A[i] < neg){
			neg = A[i];
			neg1 = 1;
		}
	}

	if(neg1){
		k += (-neg);
		for(i = 0; i < sizeA; i++)
			A[i] += (-neg);
	}
	
	int count[k];

	for(i = 0; i < k; i++)
		count[i] = 0;
	
	for(j = 0; j < sizeA; j++)
		count[A[j]]++;
	
	for(i = 1; i < k; i++)
		count[i] += count[i-1];

	for(j = 0; j < sizeA; j++){
		B[count[A[j]]] = A[j];
		count[A[j]]--;
	}
	
	if(neg1){
		for(i = 1 ; i < sizeA+1; i++)
			B[i] += neg; 
	}

}

int main(int argc, char **argv){
	
	int i = 0;
	int numLine = CountLine(argv[1]);
	int A[numLine];

	FillArray(A, argv[1]);

	int k = A[0];
	int sizeA = sizeof(A) / sizeof(int);
	int B[sizeA+1];
	struct timespec start, finish;
	double time;

	for(i = 1; i < sizeA; i++){
		if(A[i] > k)
			k = A[i];
	}
	
	clock_gettime(CLOCK_MONOTONIC, &start);
	CountingSort(A, B, k+1, sizeA);
	clock_gettime(CLOCK_MONOTONIC, &finish);

	printf("\tArray Ordenado:\n");

	for(i = 1; i < sizeA+1; i++)
		printf("\t\t%d\n", B[i]);
	
	time = (finish.tv_nsec - start.tv_nsec) / 1000000.0;
	printf("Tempo de execução do Counting Sort: %f ms\n", time);
	
	return 0;

}
