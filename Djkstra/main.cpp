#include "dijkstra.hpp"

int main(int argc, char **argv){
	vector<vector<int> > M;
	int i;
	Dijkstra d;

	d.BuildMatrixAdj(M, argv[1]);

	d.DijkstraAlgorithm(M, 0);

	return 0;
}
