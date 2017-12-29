#include <iostream>
#include "AdvancedAlgorithms.h"
#include "BasicAlgorithms.h"

template<class Data>
class LTC
{
public:
	bool operator() (const Data& a, const Data& b)
	{
		return a < b;
	}
};

template<class Data>
void printArr(const Data* arr,const int size)
{	
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << ' ';
	}
	std::cout << "\n-------------------------------\n";
}
int main()
{
	LTC<int> cmpIntegers;
	int arr[8] = { 5,2,5,1,6,15,3,7 };
	selectionSort<int>(arr, 8,cmpIntegers);
	printArr<int>(arr,8);
	std::cout << '\n';
	return 0;
}