#include <stdio.h>

void InsertionSort(int *array, int size){
      
      int i, j, aux;

      for(i = 1; i < size; i++){
         //armazena o número que vai ser comparado com os numéros anteriores
	 aux = array[i];
	 //armazena o índice do número imediatamente anterior ao que se quer comparar
	 j = i - 1;
         
         while((j >= 0) && (aux < array[j])){
              //copia o número que é maior que o aux para a próxima posição do array
              array[j + 1] = array[j];
              //decrementa a variável para fazer a comparação com todos os números anteriores
              j--;
         }
         
	 //o número que estava sendo comparado é colocado na posição correta
         array[j + 1] = aux;
      }
}

int main(){

      int array[10] = {9, 2, 7, 4, 1, 8, 0, 5, 3, 6};
      int i;
	
      printf("Array Desordenado:\n");
	
      for(i = 0; i < 10; i++)
	 printf("\t%i\n", array[i]);

      InsertionSort(array, 10);

      printf("Array Ordenado:\n");

      for(i = 0; i < 10; i++)
	 printf("\t%i\n", array[i]);

      return 0;
}
