#include "product.hpp"
#include "knapsack.hpp"
#include <iostream>
#include <fstream>

void FileReader(const char *fileName, vector<Product*> &products){
	int weight, value;
	
	ifstream file(fileName);

	while(file >> weight >> value)
		products.push_back(new Product(weight, value));

	file.close();
}

int main(int argc, char** argv){
	int capacity;
	vector<Product*> products;
	Knapsack k;

	FileReader(argv[1], products);

	capacity = products[0]->value_;
	products.erase(products.begin());

	k.FillsKnapsack(products, capacity);
	k.ShowItems(products);

	return 0;
}
