#ifndef PRIM_H
#define PRIM_H
#include "minheap.hpp"
#include <limits.h>
#include <stdio.h>
#define INFINITY INT_MAX

class Prim{
	public:
		Prim();
		void BuildMatrixAdj(vector<vector<int> > &M, char *nameTxt);
		void PrimAlgorithm(vector<vector<int> > M, int root);
		~Prim();
};

#endif
