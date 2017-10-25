#include "tsp.hpp"

int main(int argc, char** argv){
	int minCost;
	TSP p;
	
	//constrói a matriz de adjacência
	p.BuildAdjMatrix(argv[1]);
	//soluciona o problema do caixeiro viajante
	p.SolutionTSP();

	return 0;
}
