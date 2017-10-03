#include "prim.hpp"

int main(int argc, char **argv){
	vector<vector<int> > M;
	int i;
	Prim p;

	p.BuildMatrixAdj(M, argv[1]);

	for(int i = 0; i < M.size(); i++){
		cout << endl;
		for(int j = 0; j < M[i].size(); j++)
			cout << M[i][j] << "\t";
	}
	cout << endl << endl;

	p.PrimAlgorithm(M, 0);

	return 0;
}
