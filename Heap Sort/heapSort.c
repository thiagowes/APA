#include <stdio.h>

void BuildMaxHeap(int* array, int ini, int fim){
       
      int aux = array[ini];
      int j = ini * 2 + 1;

      while(j <= fim){
	//verifica se o pai tem dois filhos e qual deles é o maior
	if(j < fim){
	  if(array[j] < array[j + 1])
	    j++;
	}
	//se o filho for maior que o pai, ele se torna o pai
	if(aux < array[j]){
	  array[ini] = array[j];
	  ini = j;
	  //armazena o indice do próximo filho para repetir o processo
	  j = 2 * ini + 1;
	}
	else
	  //encerrar laço while
	  j = fim + 1;	
      }
      
      //o antigo pai é alocado na posição do último filho analisado
      array[ini] = aux;
}


void HeapSort(int *array, int size){
      
      int i, aux;
      //criando a heap
      for(i = (size - 1) / 2; i >= 0; i--)
	BuildMaxHeap(array, i, size - 1);
     
      for(i = size - 1; i >= 1; i--){
	//coloca o maior elemento da heap na posição correta
	aux = array[0];
	array[0] = array[i];
	array[i] = aux;
	//recria a heap
	BuildMaxHeap(array, 0, i - 1);
      }
}

int main(){

      int array[10] = {9, 2, 7, 4, 1, 8, 0, 5, 3, 6};
      int i;
	
      printf("Array Desordenado:\n");
	
      for(i = 0; i < 10; i++)
	 printf("\t%i\n", array[i]);

      HeapSort(array, 10);

      printf("Array Ordenado:\n");

      for(i = 0; i < 10; i++)
	 printf("\t%i\n", array[i]);

      return 0;
}
