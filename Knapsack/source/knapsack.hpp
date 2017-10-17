#ifndef KNAPSACK_H
#define KNAPSACK_H
#include "product.hpp"
#include <vector>
#include <iostream>

using namespace std;

class Knapsack{
	public:
		Knapsack();
		void FillsKnapsack(const vector<Product*> &products, const int capacity);
		void ShowItems(const vector<Product*> &products);
		~Knapsack();
	private:
		vector<vector<int> > Matrix;
		vector<int> items;
};

#endif
