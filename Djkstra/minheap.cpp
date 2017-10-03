#include "minheap.hpp"

MinHeap::MinHeap(){}

int MinHeap::LeftChild(int i){
	return (2 * i) + 1;
}

int MinHeap::RightChild(int i){
	return (2 * i) + 2;
}

void MinHeap::MinHeapify(vector<vertex> &A, int i){
	int left = LeftChild(i);
	int right = RightChild(i);
	int min;
	vertex aux;

	if(left < A.size() && A[left].cost < A[i].cost) 
		min = left;
	else
		min = i;

	if(right < A.size() && A[right].cost < A[min].cost)
		min = right;

	if(min != i){
		aux.cost = A[min].cost;
		aux.path = A[min].path;
		aux.known = A[min].known;
		aux.id = A[min].id;
		A[min].cost = A[i].cost;
		A[min].path = A[i].path;
		A[min].known = A[i].known;
		A[min].id = A[i].id;
		A[i].cost = aux.cost;
		A[i].path = aux.path;
		A[i].known = aux.known;
		A[i].id = aux.id;
		
		MinHeapify(A, min);
	}	
		
}

void MinHeap::BuildMinHeap(vector<vertex> &A){
	int i = (A.size() - 1) / 2;

	for(i; i >= 0; i--)
		MinHeapify(A, i);
}

vertex MinHeap::HeapExtractMin(vector<vertex> &A){
	if(A.size() < 0)
		cout << "heap underflow" << endl;
	
	vertex min = A[0];
	A.erase(A.begin());		
	MinHeapify(A, 0);

	return min;	
}

MinHeap::~MinHeap(){}
