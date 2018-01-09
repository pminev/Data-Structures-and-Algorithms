#pragma once
#include <iostream>
#include "SortingAlgorithms.h"

template<class Data, class Function = LTC<Data>>
void insertionSort(Data arr[], int size, Function cmp)
{
	for (size_t i = 1; i < size; i++)
	{
		int temp = arr[i];
		int size = i;
		while (cmp(temp, arr[size - 1]) && size > 0)
		{
			arr[size] = arr[size - 1];
			size--;
		}
		arr[size] = temp;
	}
}

template <class Data, class Function = LTC<Data>>
void selectionSort(Data arr[], int size, Function cmp)
{
	for (size_t i = 0; i < size; i++)
	{
		int indexToSwap = i;
		for (size_t j = i + 1; j < size; j++)
		{
			if (cmp(arr[indexToSwap], arr[j]))
				indexToSwap = j;
		}

		if (i != indexToSwap)
		{
			std::swap(arr[i], arr[indexToSwap]);
		}
	}
}

	template<class Data, class Function = LTC<Data>>
	void bubbleSort(Data arr[], int size, Function cmp)
{
	bool swapped = true;
	for (int i = size - 1; i >= 0 && swapped; i--)
	{
		swapped = false;
		for (int j = 0; j < i; j++)
		{
			if (cmp(arr[j], arr[j + 1]))
			{
				std::swap(arr[j], arr[j + 1]);
				swapped = true;
			}
		}
	}
}
