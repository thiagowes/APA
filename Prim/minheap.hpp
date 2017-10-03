#ifndef MINHEAP_H
#define MINHEAP_H
#include <iostream>
#include <vector>

using namespace std;

struct Vertex{
	int known;
	int cost;
	int path;
	int id;	
}; typedef Vertex vertex;

class MinHeap{
	public:
		MinHeap();
		int LeftChild(int i);
		int RightChild(int i);
		void MinHeapify(vector<vertex> &A, int i);
		void BuildMinHeap(vector<vertex> &A);
		vertex HeapExtractMin(vector<vertex> &A);
		~MinHeap();
};

#endif
