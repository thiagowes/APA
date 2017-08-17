#include <stdio.h>

void SelectionSort(int *array, int size){
	
     int i, j, min, aux;

     for(i = 0; i < (size-1); i++){
        //armazena o menor indice do array ainda não ordenado
	min = i; 

	for(j = (i+1); j < size; j++){
	   //verifica se existe algum valor menor no array
	   if(array[j] < array[min]) 
	     //se existir atualiza a variável min para o índice que contém o menor valor
	     min = j;
        }
	
	//verifica se a variável min foi atualizada para identificar se precisa ordenar ou não	
	if(array[i] != array[min]){
          aux = array[i];
	  array[i] = array[min];
          array[min] = aux;
	}
	
      }
}

int main(){

      int array[10] = {9, 2, 7, 4, 1, 8, 0, 5, 3, 6};
      int i;
	
      printf("Array Desordenado:\n");
	
      for(i = 0; i < 10; i++)
	 printf("\t%i\n", array[i]);

      SelectionSort(array, 10);

      printf("Array Ordenado:\n");

      for(i = 0; i < 10; i++)
	 printf("\t%i\n", array[i]);

      return 0;
}
