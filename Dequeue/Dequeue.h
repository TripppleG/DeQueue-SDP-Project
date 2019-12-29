#pragma once

template <class T>
class Dequeue
{
	int capacity;
	int size;
	T* arr;
	int startIndex;
	int endIndex;

	void CopyFrom(const Dequeue<T> other);
	void Free();
	bool IsEmpty() const;
	void Resize(const bool BackOrFront); // We would have value of 'false' for if the function is called by PushBack() and 'true' if it's called by PushFront()
public:
	Dequeue();
	Dequeue(const Dequeue<T>& other);
	Dequeue& operator=(const Dequeue<T>& other);
	~Dequeue();

	void PushFront(const T el);
	void PushBack(const T el);

	void PopFront();
	void PopBack();
	T Front() const;
	T Back() const;
};

template<class T>
inline void Dequeue<T>::CopyFrom(const Dequeue<T> other)
{
	size = other.size;
	capacity = other.capacity
	arr = new T[capacity];
	for (int i = 0; i < size; i++)
	{
		arr[i] = other.arr[i];
	}
	startIndex = other.startIndex;
	endIndex = other.endIndex;
}

template<class T>
inline void Dequeue<T>::Free()
{
	delete[]arr;
}

template<class T>
inline void Dequeue<T>::Resize(const bool BackOrFront)
{
	capacity *= 2;
	T* newArr = new T[capacity];
	if (BackOrFront)
	{
		for (int i = 0; i < size; i++)
		{
			newArr[i + 1] = arr[i];
		}
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			newArr[i] = arr[i];
		}
	}
	endIndex = size;
	startIndex = 0;
	delete[]arr;
	arr = newArr;
}

template<class T>
inline Dequeue<T>::Dequeue()
{
	capacity = 8;
	size = 0;
	arr = new T[capacity];
	startIndex = endIndex = -1;
}

template<class T>
inline Dequeue<T>::Dequeue(const Dequeue<T>& other)
{
	CopyFrom(other);
}

template<class T>
inline Dequeue<T>& Dequeue<T>::operator=(const Dequeue<T>& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return this;
}

template<class T>
inline Dequeue<T>::~Dequeue()
{
	Free();
}

template<class T>
inline void Dequeue<T>::PushFront(const T el)
{
	if (size == capacity)
	{
		Resize(true);
	}
	else if (startIndex == 0 || startIndex == -1)
	{
		startIndex == size;
	}
	else
	{
		startIndex--;
	}
	arr[startIndex] = el;
	size++;
}

template<class T>
inline void Dequeue<T>::PushBack(const T el)
{
	if (size == capacity)
	{
		Resize(false);
	}
	else if (startIndex == -1)
	{
		startIndex = endIndex = 0;
	}
	else if (endIndex == capacity - 1)
	{
		endIndex = 0;
	}
	else
	{
		endIndex++;
	}
	arr[endIndex] = el;
	size++;
}

template<class T>
inline void Dequeue<T>::PopFront()
{
	if (IsEmpty())
	{
		throw "Empty Queue";
	}
	delete arr[startIndex];
	/*if (startIndex == endIndex)
	{

	}*/
}

template<class T>
inline bool Dequeue<T>::IsEmpty() const
{
	return size == 0;
}

template<class T>
inline T Dequeue<T>::Front() const
{
	return arr[startIndex];
}

template<class T>
inline T Dequeue<T>::Back() const
{
	return arr[endIndex];
}