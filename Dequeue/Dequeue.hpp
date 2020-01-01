#pragma once

template <class T>
class Dequeue
{
	T* arr;
	int size;
	int capacity;
	int startIndex;
	int endIndex;
	bool calledByResize;

	void CopyFrom(const Dequeue<T>& other);
	void Free();
	void Resize(const bool downOrUpSize, const bool BackOrFront);
	/*
		We pass a value of 'false' to downOrUpSize when a pop function is called and we need to downsize our queue
		and a value of 'true' when a push function is called and we need to upsize our queue.

		We pass a value of 'true' to BackOrFront in the push functions to determinate if we are pushing an
		element at the front or back of our queue. It is used in order to know if we need to add a "blank" space
		in the front of the queue for the new element or not. Doesn't have any effect on the pop functions!
	*/
public:
	Dequeue();
	Dequeue(const Dequeue<T>& other);
	Dequeue& operator=(const Dequeue<T>& other);
	~Dequeue();

	bool IsEmpty() const;
	void PushFront(const T el);
	void PushBack(const T el);
	void PopFront();
	void PopBack();
	T Front() const;
	T Back() const;
};

template<class T>
inline void Dequeue<T>::CopyFrom(const Dequeue<T>& other)
{
	size = other.size;
	capacity = other.capacity;
	arr = new T[capacity];
	for (int i = 0; i < size; i++)
	{
		arr[i] = other.arr[i];
	}
	startIndex = other.startIndex;
	endIndex = other.endIndex;
	calledByResize = other.calledByResize;
}

template<class T>
inline void Dequeue<T>::Free()
{
	delete[]arr;
}

template<class T>
inline void Dequeue<T>::Resize(const bool downOrUpSize, const bool BackOrFront)
{
	T* newArr; // Creating a pointer to a new array in which we will add the elements
	if (downOrUpSize)
	{
		newArr = new T[capacity * 2];
		if (BackOrFront)
		{
			for (int i = 0; i < capacity; i++)
			{
				calledByResize = true;   // Tells the pop functions that they are called in the Resize function to avoid getting in recursion
				newArr[i + 1] = Front(); // The index is i + 1 because we want to leave one free space for the new
				PopFront();				 // which will be added after the resize
			}
		}
		else
		{
			for (int i = 0; i < capacity; i++)
			{
				calledByResize = true;
				newArr[i] = Front();
				PopFront();
			}
		}
		size = capacity; // Since after calling PopFront() the size is changed we need to set it with the right value again
		capacity *= 2;
		startIndex = 0;  // Moving the startIndex to the beginning of the array
		endIndex = size; // Moving endIndex to the end of the array
	}
	else
	{
		int newCapacity = capacity / 2;
		newArr = new T[newCapacity];
		for (int i = 0; i < newCapacity; i++)
		{
			calledByResize = true;
			newArr[i] = Front();
			PopFront();
		}
		capacity = newCapacity;
		size = capacity;
		startIndex = 0; // Moving endIndex to the end of the array
		endIndex = size - 1; // Moving endIndex to the end of the array. Here we have -1 because in the pop functions, unlike in the push
	}						 // functions, the change of the size is made BEFORE the Resize function
	delete[]arr; // Deleting the old array
	arr = newArr; // Moving the arr pointer so it points to the new array
}

template<class T>
inline Dequeue<T>::Dequeue()
{
	capacity = 4; // TODO: Change the size to 256
	size = 0;
	arr = new T[capacity];
	startIndex = endIndex = -1;
	calledByResize = false;
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
	return *this;
}

template<class T>
inline Dequeue<T>::~Dequeue()
{
	Free();
}

template<class T>
inline bool Dequeue<T>::IsEmpty() const
{
	return size == 0;
}

template<class T>
inline void Dequeue<T>::PushFront(const T el)
{
	if (size == capacity)
	{
		Resize(true, true); // true for downOrUpSize and true for BackOrFront
	}
	else if (startIndex == -1)
	{
		startIndex = endIndex = 0; // Moving both the indexes to the first posision in case this is the first element we add
	}
	else if (startIndex == 0)
	{
		startIndex = capacity - 1; //Moving the start index at the end of the queue in case
	}
	else
	{
		startIndex--; // If the index is in the range of [1; capacity - 1) we move it one position to the left
	}
	arr[startIndex] = el;
	size++;
}

template<class T>
inline void Dequeue<T>::PushBack(const T el)
{
	if (size == capacity)
	{
		Resize(true, false); // true for downOrUpSize and false for BackOrFront
	}
	else if (startIndex == -1) 
	{
		startIndex = endIndex = 0; // Moving both the indexes to the first posision in case this is the first element we add
	}
	else if (endIndex == capacity - 1)
	{
		endIndex = 0; // Moving the index to the beginning of the array in case it is at the end
	}
	else
	{
		endIndex++; // If the index is in the range of [1; capacity - 1) we move it one position to the right
	}
	arr[endIndex] = el;
	size++;
}

template<class T>
inline void Dequeue<T>::PopFront()
{
	if (IsEmpty())
	{
		throw std::runtime_error("Empty Queue!");
	}
	if (startIndex == endIndex)
	{
		startIndex = endIndex = -1; // startIndex == endIndex means that the element we are removing is the last one in the queue, so we
	}								// are setting the indexes in a starting position
	else if(startIndex == capacity - 1)
	{
		startIndex = 0; // Moving the index to the beginning of the array in case it is at the end
	}
	else
	{
		startIndex++; // If the index is in the range of [1; capacity - 1) we move it one position to the right
	}
	size--;
	if (2 * size == capacity && !calledByResize) // Downsize the array if 2 * size == capacity AND the current pop function is NOT called by
	{											 // the Resize function
		Resize(false, true); // false for downOrUpSize and true for BackOrFront
	}
	calledByResize = false; // Setting the value to false in case we pop enough elements to have the need for downsizing
}

template<class T>
inline void Dequeue<T>::PopBack()
{
	if (IsEmpty())
	{
		throw std::runtime_error("Empty Queue!");
	}
	if (startIndex == endIndex)
	{
		startIndex = endIndex = -1; // startIndex == endIndex means that the element we are removing is the last one in the queue, so we
	}								// are setting the indexes in a starting position
	else if (endIndex == 0)
	{
		endIndex = capacity - 1; // Moving the index to the end of the array in case it is at the beginning
	}
	else
	{
		endIndex--; // If the index is in the range of [1; capacity - 1) we move it one position to the left
	}
	size--;
	if (2* size == capacity && !calledByResize) // Downsize the array if 2 * size == capacity AND the current pop function is NOT called by
	{											// the Resize function
		Resize(false, false); // false for downOrUpSize and false for BackOrFront
	}
	calledByResize = false; // Setting the value to false in case we pop enough elements to have the need for downsizing
}

template<class T>
inline T Dequeue<T>::Front() const
{
	if (IsEmpty())
	{
		throw std::runtime_error("Empty Queue!");
	}
	return arr[startIndex];
}

template<class T>
inline T Dequeue<T>::Back() const
{
	if (IsEmpty())
	{
		throw std::runtime_error("Empty Queue!");
	}
	return arr[endIndex];
}