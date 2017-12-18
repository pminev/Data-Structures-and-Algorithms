#pragma once
#include "assert.h"

template<class T>
class Queue
{

private:
	void Init();
	void Destroy();
	void CopyFrom(const Queue&);

	
public:
		Queue();
		Queue(const Queue&);
		Queue& operator=(const Queue&);
		~Queue();
	
public:
		void Push(const T&);
		void Pop();
		const T& Peek();

		bool isEmpty() const;
		size_t getSize();

private:

	struct node
	{
		T data;
		node* next;

		node(T newData, node* newPointer = nullptr)
		{
			data = newData;
			next = newPointer;
		}


	};

	node* Front;
	node* Back;
	size_t CurSize;

};

template<class T>
inline void Queue<T>::Init()
{
	Front = nullptr;
	Back = nullptr;
	CurSize = 0;
}

template<class T>
inline void Queue<T>::Destroy()
{
	node* destroyer;
	while (Front!=nullptr)
	{
		destroyer = Front;
		Front = Front->next;

		delete destroyer;
	}
	Init();
}

template<class T>
inline void Queue<T>::CopyFrom(const Queue & other)
{
	if (other.isEmpty())
	{
		return;
	}

	try
	{
		Front = new node(other.Front->data);

		node* copy = other.Front;
		node* copier = Front;

		while (copy->next!=nullptr)
		{
			copy = copy->next;

			copier->next = new node(copy->data);
			copier = copier->next;
		}

		Back = copier;
		CurSize = other.CurSize;

	}
	catch (const std::bad_alloc&)
	{
		Destroy();
		throw;
	}

}

template<class T>
inline Queue<T>::Queue()
{
	Init();
}

template<class T>
inline Queue<T>::Queue(const Queue & other)
{
	Init();
	CopyFrom(other);
}

template<class T>
inline Queue<T>& Queue<T>::operator=(const Queue& other)
{
	if (this!=&other)
	{
		Destroy();
		CopyFrom(other);
	}

	return *this;
}

template<class T>
inline Queue<T>::~Queue()
{
	Destroy();
}

template<class T>
inline void Queue<T>::Push(const T & data)
{
	if (isEmpty())
	{
		Front = new node(data);
		Back = Front;
		CurSize++;
		return;
	}
	node* newNode = new node(data);

	newNode->next = Front;
	Front = newNode;

	CurSize++;
	
}

template<class T>
inline void Queue<T>::Pop()
{
	if (isEmpty())
	{
		assert("The Queue is empty!");
	}
	if (CurSize==1)
	{
		Init();
		return;
	}
	node* it = Front;

	while (it->next!=Back)
	{
		it = it->next;
	}
		
	delete Back;
	Back = it;
	Back->next = nullptr;

	CurSize--;
}

template<class T>
inline const T & Queue<T>::Peek()
{
	if (isEmpty())
	{
		assert("The queue is empty");
	}

	return Back->data;


}

template<class T>
inline bool Queue<T>::isEmpty() const
{
	return CurSize == 0;
}

template<class T>
inline size_t Queue<T>::getSize()
{
	return CurSize;
}
