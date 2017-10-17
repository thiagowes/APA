#ifndef PRODUCT_H
#define PRODUCT_H

class Product{
	public:
		Product(int weight, int value);
		~Product();

		int weight_;
		int value_;
};

#endif
