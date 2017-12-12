#include <iostream>
#include <random>
#include <ctime>
#include "BST.h"

void insertNrandomElemets(BST& tree, unsigned numberOfElements,int to)
{
	int key, value,sign;
	for (size_t i = 0; i < numberOfElements; i++)
	{
		sign = rand() % 2;
		key = sign? rand()%to:-(rand()%to);
		sign = rand() % 2;
		value = sign ? rand() % to : -(rand() % to);
		std::cout << "Trying to insert element with key " << key
			      <<" and value "<< value << " -- ";
		try
		{
			tree.insert(key, value);
			std::cout << "Successful! \n";
		}
		catch (const std::logic_error& e)
		{
			std::cout << e.what();
		}

	}
}

void removeNrandomElemets(BST& tree, unsigned numberOfElements,int to)
{
	int key, value,sign;
	for (size_t i = 0; i < numberOfElements; i++)
	{
		sign = rand() % 2;
		key = sign ? rand() % to : -(rand() % to);
		std::cout << "Trying to remove element with key " << key << " -- ";
		try
		{
			tree.remove(key);
			std::cout << "Successful! \n";
		}
		catch (const std::logic_error& e)
		{
			std::cout << e.what();
		}

	}
}
int main()
{
	srand(std::time(nullptr));
	BST tree;
	insertNrandomElemets(tree, 10,20);
	std::cout << "\n\n-----------------------------------------------\n\n";
	removeNrandomElemets(tree, 4, 16);
	return 0;
}