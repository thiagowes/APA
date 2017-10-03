#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "minheap.hpp"
#include <limits.h>
#include <stdio.h>
#define INFINITY INT_MAX

class Dijkstra{
	public:
		Dijkstra();
		void BuildMatrixAdj(vector<vector<int> > &M, char *nameTxt);
		void DijkstraAlgorithm(vector<vector<int> > M, int root);
		~Dijkstra();
};

#endif
