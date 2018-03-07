#pragma once

template<class Data>
class LTC
{
public:
	bool operator() (const Data& a, const Data& b)
	{
		return a < b;
	}
};

template<class Data, class Function = LTC<Data>>
void insertionSort(Data arr[], int size, Function cmp = LTC<Data>());

template <class Data, class Function = LTC<Data>>
void selectionSort(Data arr[], int size, Function cmp =LTC<Data>());

template<class Data, class Function = LTC<Data>>
void bubbleSort(Data arr[], int size, Function cmp = LTC<Data>());

template<class Data, class Function = LTC<Data>>
void heapSort(Data arr[], const int size, Function cmp = LTC<Data>());

template <class Data, class Function = LTC<Data>>
void quickSort(Data arr[], const int size, Function cmp = LTC<Data>());

template <class Data, class Function = LTC<Data>>
void mergeSort(Data arr[], const int size, Function cmp = LTC<Data>());
