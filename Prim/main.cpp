#include "prim.hpp"

int main(int argc, char **argv){
	vector<vector<int> > M;
	int i;
	Prim p;

	p.BuildMatrixAdj(M, argv[1]);

	p.PrimAlgorithm(M, 0);

	return 0;
}
