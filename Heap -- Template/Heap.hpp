#pragma once
#include <iostream>
#include <assert.h>

template<class T>
class Heap
{
private:
	T* arr;
	int size;
	int cap;

public:
	Heap();
	Heap(int);
	Heap(const Heap&);
	Heap& operator=(const Heap&);
	~Heap();

	void Insert(T);
	void Remove();
	const T& getMin();
	void PrintArr()
	{
		for (int i = 1; i <= size; i++)
		{
			std::cout << arr[i] << ' ';
		}
		std::cout << '\n';
	}



private:
	void SiftUp(int);
	void SiftDown();

};

template<class T>
Heap<T>::Heap()
{
	size = 0;
	cap = 256;
	arr = new T[256];
}

template<class T>
Heap<T>::Heap(int n)
{
	size = 0;
	cap = n;
	arr = new T[n];
}
template<class T>
Heap<T>::Heap(const Heap& other)
{
	size = other.size;
	cap = other.cap;
	arr = new T[cap];

	for (int i = 0; i <= size; i++)
	{
		arr[i] = other.arr[i];
	}
}

template<class T>
Heap<T>& Heap<T>::operator=(const Heap<T>& other)
{
	if (this!=&other)
	{
		delete[] arr;

		size = other.size;
		cap = other.cap;
		arr = new T[cap];

		for (int i = 0; i < size; i++)
		{
			arr[i] = other.arr[i];
		}
	}

	return *this;
}

template<class T>
Heap<T>::~Heap()
{
	delete[] arr;
}

template<class T>
void Heap<T>::SiftUp(int n)
{
	
		T temp=arr[n];
		int par = size / 2;
		while (par>=1)
		{
			if (temp<arr[par])
			{
				arr[n] = arr[par];
				assert(par >= 0 &&par < cap);
				assert(n >= 0 && n < cap);
				n = par;
			}
			par /= 2;
		}

		arr[n] = temp;	
		assert(n >= 0 && n < cap);

		
}

template<class T>
void Heap<T>::SiftDown()
{
	int par = 1;
	int child = 2;
	T temp = arr[1];

	while (child<=size)
	{
		if (child+1<size)
		{
			if (arr[child+1]<arr[child])
			{ 
				assert(child >= 0 && child < cap);
				assert(child+1 >= 0 && child+1 < cap);


				child++;
			}
		}

		
		if (temp>arr[child])
		{
			arr[par] = arr[child];
			assert(par >= 0 && par < cap);
			assert(child >= 0 && child < cap);

			par = child;
			child *= 2;
		}	
		else break;
	}
		
	arr[par] = temp;
	assert(par >= 0 && par < cap);

}

template<class T>
void Heap<T>::Insert(T n)
{	
	size++;
	assert(size >= 0 && size < cap);
	arr[size] = n;
	assert(size >= 0 && size < cap);
	T temp2 = arr[size];
	SiftUp(size);
}

template<class T>
void Heap<T>::Remove()
{
	T temp = arr[1];
	assert(size >= 0 && size < cap);

	arr[1] = arr[size];
	assert(size >= 0 && size < cap);

	arr[size] = temp;
	assert(size >= 0 && size < cap);


	size--;
	assert(size >= 0 && size < cap);

	SiftDown();
}

template<class T>
const T& Heap<T>::getMin()
{
	return arr[1];
}