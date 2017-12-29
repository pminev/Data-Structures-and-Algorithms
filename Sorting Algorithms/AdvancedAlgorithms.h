#pragma once
#include <iostream>

void siftDown(int arr[], int parent, int size)
{
	int child = 2 * parent + 1;
	while (child<size)
	{
		if (arr[child]<arr[child + 1])
		{
			child++;
		}

		if (arr[parent]<arr[child])
		{
			std::swap(arr[parent], arr[child]);
			parent = child;
			child = 2 * parent + 1;
		}
		else
		{
			break;
		}
	}
}

void buildHeap(int arr[], int size)
{
	int lastParent = size / 2 - 1;
	for (int i = lastParent; i >= 0; i--)
	{
		siftDown(arr, i, size);
	}
}

void heapSort(int arr[], int size)
{
	buildHeap(arr, size);

	for (int i = size - 1; i >0; i--)
	{
		std::swap(arr[0], arr[i]);
		siftDown(arr, 0, size);
	}
}