#include <stdio.h>

int Particiona(int *array, int ini, int fim){
    
      int esq = ini, dir = fim, pivo = array[ini], aux;

      while(esq < dir){
	//incrementa até encontrar um número menor ou igual o pivo
	while(array[esq] <= pivo)
	  esq++;
	//decrementa até encontrar um número maior que o pivo
	while(array[dir] > pivo)
	  dir--;
	//executa a troca, colocando o menor a esquerda do pivo e o maior a direita
	if(esq < dir){
	  aux = array[esq];
	  array[esq] = array[dir];
	  array[dir] = aux;
	}
      }
      //faz a troca, colocando o pivo no seu lugar correto
      array[ini] = array[dir];
      array[dir] = pivo;
      
      return dir;
}

void QuickSort(int *array, int ini, int fim){
     
      int pivo;
	
      if(fim > ini){
	//chama a função para determinar o pivo e particionar o vetor
	pivo = Particiona(array, ini, fim);
	//chama a função para as duas metades do array
	QuickSort(array, ini, pivo - 1);
	QuickSort(array, pivo + 1, fim);
      }
}


int main(){

      int i;
      int array[10] = {9, 2, 7, 4, 1, 8, 0, 5, 3, 6};
	
      printf("Array Desordenado:\n");
	
      for(i = 0; i < 10; i++)
	 printf("\t%i\n", array[i]);

      QuickSort(array, 0, 9);

      printf("Array Ordenado:\n");

      for(i = 0; i < 10; i++)
	 printf("\t%i\n", array[i]);

      return 0;
}
