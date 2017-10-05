#include "prim.hpp"

Prim::Prim(){}

void Prim::BuildMatrixAdj(vector<vector<int> > &M, char *nameTxt){
	vector<int> aux;
	int number;
	
	FILE *arq;
	
	arq = fopen(nameTxt, "r");

	if(arq == NULL)
		cout << "Error opening file" << endl;
	
	while(!feof(arq)){
		fscanf(arq, "%d", &number);
		aux.push_back(number);
	}
	
	fclose(arq);

	M.resize(aux[0]);

	int t = 1;

	for(int i = 0; i < aux[0]; i++){
		M[i].resize(aux[0]);
		for(int j = 0; j < aux[0]; j++){
			if(j == i)
				M[i][j] = 0;
			else if(j > i){
				M[i][j] = aux[t];
				t++;
			}
			else if(i > j)
				M[i][j] = M[j][i];
		}
	}
	
}

void Prim::PrimAlgorithm(vector<vector<int> > M, int root){
	int costT = 0, sizeAux;
	MinHeap minH;
	vertex minV;
	vector<vertex> V;
	vector<vertex> auxV;
	V.resize(M.size());

	for(int i = 0; i < V.size(); i++){
		V[i].id = i;
		V[i].cost = INFINITY;
		V[i].path = -1;
		V[i].known = 0;
	}

	cout << "Root: " << root << endl << endl;

	V[root].cost = 0;

	while(V[root].known != 1){
		V[root].known = 1;

		for(int i = 0; i < M.size(); i++){
			if(V[i].known == 0 && M[root][i] > 0 && M[root][i] < V[i].cost){
				V[i].cost = M[root][i];
				V[i].path = root;	
			}
			if(V[i].known == 0)
				auxV.push_back(V[i]);
		}

		minH.BuildMinHeap(auxV);
		if(auxV.size() > 0)
			minV = minH.HeapExtractMin(auxV);
		root = minV.id;
		
		sizeAux = auxV.size();

		for(int i = 0; i < sizeAux; i++)
			auxV.erase(auxV.begin());
	}	
	
	for(int i = 0; i < V.size(); i++){
		costT += V[i].cost;
		cout << "Vertices(" << V[i].path << "," << V[i].id << ")"
			 << "\t" << "Cost: " << V[i].cost << endl;
	}

	cout << endl << "Total Cost: " << costT << endl;
				
}

Prim::~Prim(){}
		

