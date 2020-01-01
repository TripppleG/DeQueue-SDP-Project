#include <iostream>
#include "Dequeue.h"

int main()
{
	Dequeue<int> deq;
	deq.PushBack(1);
	deq.PushBack(2);
	deq.PushBack(3);
	deq.PushBack(4);
	deq.PopFront();
	deq.PushBack(6);
	deq.PushBack(8);
	deq.PushBack(5);
	deq.PushBack(6);
	deq.PushBack(7);
	deq.PushBack(8);
	deq.PushBack(9);
	deq.PopFront();
	deq.PopFront();
	deq.PopFront();
	deq.PopBack();
	deq.PopFront();
	deq.PopFront();
	deq.PopBack();
	deq.PopBack();
	deq.PopFront();
	deq.PopBack();
	
	return 0;
}