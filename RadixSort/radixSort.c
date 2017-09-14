#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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

void RadixSort(int *A, int d){
	int i;
	int B[d + 1];
	int max = A[0];
	int div = 1;
	int neg = 0;
	int neg1 = 0;

	for(i = 0; i < d; i++){
		if(A[i] < neg){
			neg = A[i];
			neg1 = 1;
		}
	}

	if(neg1){
		for(i = 0; i < d; i++)
			A[i] += (-neg);
	}

	for(i = 0; i < d; i++){
		if(max < A[i])
			max = A[i];
	}

	while(max / div > 0){
		int count[10] = {0};

		for(i = 0; i < d; i++)
			count[(A[i] / div) % 10]++;

		for(i = 1; i < 10; i++)
			count[i] += count[i - 1];
	
		for(i = d - 1; i >= 0; i--){
			B[count[(A[i] / div) % 10]] = A[i];
			count[(A[i] / div) % 10]--;
		}
		for(i = 0; i < d; i++)
			A[i] = B[i + 1];
		div *= 10;
	}

	if(neg1){
		for(i = 0 ; i < d; i++)
			A[i] += neg; 
	}
	
}

int main(int argc, char **argv){
	int i = 0;
	int numLine = CountLine(argv[1]);
	int A[numLine];

	FillArray(A, argv[1]);

	int size = sizeof(A) / sizeof(int);
	struct timespec start, finish;
	double time;	
	
	clock_gettime(CLOCK_MONOTONIC, &start);
	RadixSort(A, size);
	clock_gettime(CLOCK_MONOTONIC, &finish);
	
	printf("\tArray Ordenado:\n");

	for(i = 0; i < size; i++)
		printf("\t\t%d\n", A[i]);

	time = (finish.tv_nsec - start.tv_nsec) / 1000000.0;
	printf("Tempo de execução do Radix Sort: %f ms\n", time);

	return 0;
}
