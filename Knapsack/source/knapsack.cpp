#include "knapsack.hpp"

Knapsack :: Knapsack() {}

void Knapsack :: FillsKnapsack(const vector<Product*> &products, const int capacity){	
	
	Matrix.resize(products.size());

	for(int i = 0; i < Matrix.size(); i++){
		Matrix[i].resize(capacity + 1);
		for(int j = 0; j < Matrix[i].size(); j++){
			if(j == 0 || products[i]->weight_ > j && i == 0)
				Matrix[i][j] = 0;
			else if(products[i]->weight_ <= j && i == 0)
				Matrix[i][j] = products[i]->value_;
			else if(products[i]->weight_ <= j && i != 0)
				Matrix[i][j] = max(products[i]->value_ + Matrix[i-1][j-products[i]->weight_], Matrix[i-1][j]);
			else
				Matrix[i][j] = 	Matrix[i-1][j];
		}
	}

	cout << "Valor: " << Matrix[Matrix.size() - 1][Matrix[0].size() - 1] << endl;
	
}

void Knapsack :: ShowItems(const vector<Product*> &products){
	int j = Matrix[0].size() - 1;
	int i = Matrix.size() - 1;

	for(i; i >= 0; i--){
		if(Matrix[i][j] == 0)
			break;
		else if(i == 0 && Matrix[i][j] != 0){
			items.push_back(i+1);
			break;
		}

		if(Matrix[i][j] != Matrix[i-1][j]){
			j -= products[i]->weight_;
			items.push_back(i+1);
		}
	}

	cout << "Produtos Escolhidos: ";
	for(int i = items.size() - 1; i >= 0; i--){
		if(i == 0)
			cout << items[i] << endl;
		else			
			cout << items[i] << ", ";
	}
}
	

Knapsack :: ~Knapsack() {}
