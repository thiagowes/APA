#include <stdio.h>
#include <stdlib.h>


void Merge(int ini, int meio, int fim, int *array){
      
      int *auxV;
      int com1 = ini, com2 = meio + 1, fim1 = 0, fim2 = 0, i, j, k;
      
      auxV = (int *) malloc(((fim - ini) + 1) * sizeof(int));
      
      //percorre o vetor auxiliar
      for(i = 0; i < ((fim - ini) + 1); i++){
	//verifica se o vetor(as duas metades) chegou ao final
        if(!fim1 && !fim2){
          //verifica qual é o menor número e armzena no vetor auxiliar
	  if(array[com1] < array[com2])
	    auxV[i] = array[com1++];
	  else
	    auxV[i] = array[com2++];
	
          //verifica se o vetor acabou
	  if(com1 > meio)
	    fim1 = 1;

	  if(com2 > fim)
	    fim2 = 1;
	}
	else{
	  //armazena os números que faltam no vetor auxiliar
	  if(!fim1)
	    auxV[i] = array[com1++];
	  else
	    auxV[i] = array[com2++];
        }
      }

      //copia o vetor auxiliar para o original
      for(j = 0, k = ini; j < ((fim - ini) + 1); j++, k++)
	array[k] = auxV[j];

      free(auxV);
}

void MergeSort(int *array, int ini, int fim){
      
      int meio;
      
      if(ini < fim){
	//calcula o meio do vetor
	meio = (ini + fim)/2;
	//chama a função para as duas metades
	MergeSort(array, ini, meio);
	MergeSort(array, meio + 1, fim);
	//chama a função para ordenar comparando uma metade com a outra
	Merge(ini, meio, fim, array);
      }
}

int main(){

      int i;
      int array[10] = {9, 2, 7, 4, 1, 8, 0, 5, 3, 6};
	
      printf("Array Desordenado:\n");
	
      for(i = 0; i < 10; i++)
	 printf("\t%i\n", array[i]);

      MergeSort(array, 0, 9);

      printf("Array Ordenado:\n");

      for(i = 0; i < 10; i++)
	 printf("\t%i\n", array[i]);

      return 0;
}
