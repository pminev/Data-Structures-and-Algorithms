#include <iostream>
#include "SortingAlgorithms.h"
#include <stdlib.h>
#include <fstream>
#include <random>
#include <time.h>
#include <cstdio>
#include <ctime>
#include <chrono>

/*
	Testing the speed of types of sorting Algorithms
	1.Qsort -> stdlib
	2.STD::sort 
	3.STD::stable_sort
	4.My Quicksort -> handwritten
*/

const int MAX = 100000;

bool isSorted(int arr[], int size)
{
	for (int i = 1; i < size; i++)
	{
		if (arr[i - 1] < arr[i])
		{
			std::cout << "arr[" << i << "] = " << arr[i] << '\n';
			std::cout << "arr[" << i-1 << "] = " << arr[i-1] << '\n';
			return false;
		}
	}
	return true;
}

template<class Data>
void printArr(const Data* arr, const int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << ' ';
	}
	std::cout << "\n-------------------------------\n";
}

int cmpfunc(const void * a, const void * b) {
	return (*(int*)a - *(int*)b);
}

int cmpfunc2(const void * a, const void * b) {
	return (*(int*)b - *(int*)a);
}

void stdSort(int arr[], int size)
{
	int tempArr[MAX];
	for (int i = 0; i < MAX; i++)
	{
		tempArr[i] = arr[i];
	}
	
	auto beg = std::chrono::system_clock::now();
	std::sort(tempArr, tempArr + MAX, [](int a, int b) {return a > b; });
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> duration = end - beg;
	std::cout << "STD quicksort " << duration.count() << "s " << (isSorted(tempArr, MAX) ? " Sorted" : " Not Sorted") << '\n';
	
}

void stableSort(int arr[], int size)
{
	int tempArr[MAX];
	for (int i = 0; i < MAX; i++)
	{
		tempArr[i] = arr[i];
	}

	auto beg = std::chrono::system_clock::now();
	std::stable_sort(tempArr, tempArr + MAX, [](int a, int b) {return a > b; });
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> duration = end - beg;
	std::cout << "STD stable sort " << duration.count() << "s " << (isSorted(tempArr, MAX) ? " Sorted" : " Not Sorted") << '\n';
	
}

void sortqSort(int arr[], int size)
{	
	int tempArr[MAX];
	for (int i = 0; i < MAX; i++)
	{
		tempArr[i] = arr[i];
	}

	auto beg = std::chrono::system_clock::now();
	std::qsort(tempArr, MAX, sizeof(int), cmpfunc2);
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> duration = end - beg;
	std::cout << "Quicksort stdlib" << duration.count() << "s " << (isSorted(tempArr, MAX) ? " Sorted" : " Not Sorted") << '\n';

}

void myQS(int arr[], int size)
{
	int tempArr[MAX];
	for (int i = 0; i < MAX; i++)
	{
		tempArr[i] = arr[i];
	}

	auto beg = std::chrono::system_clock::now();
	quickSort(tempArr, size, [](int a, int b) {return a < b; });
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> duration = end - beg;
	std::cout << "My QS " << duration.count() << "s " << (isSorted(tempArr, MAX) ? " Sorted" : " Not Sorted") << '\n';

}

int main()
{
	srand(time(NULL));
	/*std::ofstream ofs("rand.txt");
	for (int i = 0; i < MAX; i++)
	{
		ofs << rand() % MAX<<' ';
	}
	ofs.close();*/
	int arr[MAX];
	std::ifstream ifs("rand.txt");
	for (int i = 0; i < MAX; i++)
	{
		ifs>>arr[i];
	}
	ifs.close();

	stableSort(arr, MAX);
	stdSort(arr, MAX);
	sortqSort(arr, MAX);
	myQS(arr, MAX);
	return 0;
}