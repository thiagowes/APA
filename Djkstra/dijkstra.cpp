#include "dijkstra.hpp"

Dijkstra::Dijkstra(){}

void Dijkstra::BuildMatrixAdj(vector<vector<int> > &M, char *nameTxt){
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

void Dijkstra::DijkstraAlgorithm(vector<vector<int> > M, int root){
	int auxPath, sizeAux;
	MinHeap minH;
	vertex minV;
	vector<vector<int> > allPath;
	vector<vertex> V;
	vector<vertex> auxV;
	V.resize(M.size());
	allPath.resize(M.size());

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
			if(V[i].known == 0 && M[root][i] > 0 && V[root].cost + M[root][i] < V[i].cost){
				V[i].cost = V[root].cost + M[root][i];
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

	for(int i = 0; i < allPath.size(); i++){
		auxPath = V[i].path;
		allPath[i].push_back(i);
	
		while(auxPath > 0){
			allPath[i].push_back(auxPath);
			auxPath = V[auxPath].path;
		}
		if(i != 0)
			allPath[i].push_back(0);		
	}	
	
	for(int i = 0; i < V.size(); i++){
		if(V[i].cost < 10)
			cout << "Vertice: " << V[i].id << "\t" << "Cost: " << V[i].cost << "\t\t" << "All Path: ";	
		else
			cout << "Vertice: " << V[i].id << "\t" << "Cost: " << V[i].cost << "\t" << "All Path: ";
		for(int j = allPath[i].size() - 1; j >= 0; j--)
			cout << allPath[i][j] << " ";
		cout << endl;
	}
				
}

Dijkstra::~Dijkstra(){}
		

