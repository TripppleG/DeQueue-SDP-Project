#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include "Dequeue.hpp"
#include "doctest.h"


TEST_CASE("Testing IsEmpty() function.")
{
	std::cout << "Test case 1 - IsEmpty():\n";
	static int subcases = 1;
	Dequeue<int> deq;
	SUBCASE("When queue is empty.")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout << "Testing if the queue is empty.\n";
		CHECK(deq.IsEmpty());
		subcases++;
	}
	SUBCASE("When queue is NOT empty")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout << "Testing if the queue is NOT empty\n";
		deq.PushBack(1);
		CHECK_FALSE(deq.IsEmpty());
		subcases++;
	}
	SUBCASE("When the queue was not empty, then an element is pushed and then popped.")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout << "The queue is initially empty.\n";
		CHECK(deq.IsEmpty());
		deq.PushFront(2);
		std::cout << "We add an element through PushFront()\n";
		CHECK_FALSE(deq.IsEmpty());
		std::cout << "And we pop it through PopBack()\n";
		deq.PopBack();
		CHECK(deq.IsEmpty());
	}
	std::cout << std::endl;
}

TEST_CASE("Testing PushFront() function.")
{
	std::cout << "Test case 2 - PushFront():\n";
	Dequeue<int> deq;
	static int subcases = 1;
	SUBCASE("If there are no elements /queue is empty/.")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout << "Adding the first element of the queue: \n";
		deq.PushFront(5);
		CHECK_EQ(deq.Front(), 5);
		CHECK_EQ(deq.Front(), deq.Back());
		CHECK_EQ(deq.GetSize(), 1);
		subcases++;
	}
	SUBCASE("If the startIndex points to the beginning of the queue and we add another element.")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout <<  "Adding two elements in an empty queue through PushFront() \n";
		deq.PushFront(1);
		deq.PushFront(2);
		CHECK_EQ(deq.GetStartIndex(), deq.GetCapacity() - 1);
		subcases++;
	}
	SUBCASE("If the queue is full and we need to resize upwards.")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout << "Adding capacity + 1 elements: \n";
		deq.PushFront(1);
		deq.PushFront(2);
		deq.PushFront(6);
		deq.PushFront(24);
		deq.PushFront(120);
		CHECK_EQ(deq.Front(), 120);
		CHECK_EQ(deq.Back(), 1);
		CHECK_EQ(deq.GetCapacity(), 8);
		CHECK_EQ(deq.GetSize(), 5);
		CHECK_EQ(deq.GetStartIndex(), 0);
		CHECK_EQ(deq.GetEndIndex(), deq.GetSize() - 1);
		subcases++;
	}
	SUBCASE("If there are N elements, where 1 < N < capacity.")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout << "Adding the three(more than 1, less than capacity) elements in the queue: \n";
		deq.PushBack(10);
		deq.PushBack(15);
		deq.PushFront(20);
		CHECK_EQ(deq.Back(), 15);
		CHECK_EQ(deq.GetEndIndex(), 1);
		CHECK_EQ(deq.GetSize(), 3);
		subcases++;
	}
	std::cout << std::endl;
}

TEST_CASE("Testing PushBack() function.")
{
	std::cout << "Test case 3 - PushBack():\n";
	Dequeue<int> deq;
	static int subcases = 1;
	SUBCASE("If there are no elements /queue is empty/.")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout << "Adding the first element of the queue: \n";
		deq.PushBack(10);
		CHECK_EQ(deq.Back(), 10);
		CHECK_EQ(deq.Front(), deq.Back());
		CHECK_EQ(deq.GetSize(), 1);
		subcases++;
	}
	SUBCASE("If the endIndex points to the end of the queue and we add another element.")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout << "Adding four elements in an empty queue through PushBack(), then popping one from the front and pushing another on it's place\n";
		deq.PushBack(1);
		deq.PushBack(2);
		deq.PushBack(3);
		deq.PushBack(4);
		deq.PopFront();
		deq.PushBack(5);
		CHECK_EQ(deq.GetEndIndex(), 0);
		subcases++;
	}
	SUBCASE("If the queue is full and we need to resize upwards.")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout << "Adding capacity + 1 elements via PushBack(): \n";
		deq.PushBack(1);
		deq.PushBack(2);
		deq.PushBack(6);
		deq.PushBack(24);
		deq.PushBack(120);
		CHECK_EQ(deq.Front(), 1);
		CHECK_EQ(deq.Back(), 120);
		CHECK_EQ(deq.GetCapacity(), 8);
		CHECK_EQ(deq.GetSize(), 5);
		CHECK_EQ(deq.GetStartIndex(), 0);
		CHECK_EQ(deq.GetEndIndex(), deq.GetSize() - 1);
		subcases++;
	}
	SUBCASE("If there are N elements, where 1 < N < capacity.")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout << "Adding the three(more than 1, less than capacity) elements in the queue: \n";
		deq.PushBack(10);
		deq.PushBack(15);
		deq.PushBack(20);
		CHECK_EQ(deq.Back(), 20);
		CHECK_EQ(deq.GetEndIndex(), 2);
		CHECK_EQ(deq.GetSize(), 3);
		subcases++;
	}
	std::cout << std::endl;
}

TEST_CASE("Testing PopFront() function.")
{
	std::cout << "Test case 4 - PopFront():\n";
	Dequeue<int> deq;
	static int subcases = 1;
	SUBCASE("If we pop in an empty queue.")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout << "Popping when the queue is empty.\n";
		CHECK_THROWS(deq.PopFront());
		subcases++;
	}
	SUBCASE("If the startIndex points to the end of the queue and we pop an element.")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout << "Adding elements in a way that startIndex points to the end of the queue then popping the front element. \n";
		deq.PushFront(1);
		deq.PushFront(2);
		CHECK_EQ(deq.GetStartIndex(), 3);
		deq.PopFront();
		CHECK_EQ(deq.GetStartIndex(), 0);
		CHECK_EQ(deq.GetEndIndex(), deq.GetStartIndex());
		subcases++;
	}
	SUBCASE("If the the size of the queue is equal to capacity / 2 and we need to resize downwards.")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout << "Adding capacity + 1 elements, then popping one with PopFront():\n";
		deq.PushBack(1);
		deq.PushBack(2);
		deq.PushBack(3);
		deq.PushBack(4);
		deq.PushBack(5);
		CHECK_EQ(deq.GetCapacity(), 8);
		deq.PopFront();

		CHECK_EQ(deq.Front(), 2);
		CHECK_EQ(deq.Back(), 5);
		CHECK_EQ(deq.GetCapacity(), 4);
		CHECK_EQ(deq.GetSize(), 4);
		CHECK_EQ(deq.GetStartIndex(), 0);
		CHECK_EQ(deq.GetEndIndex(), deq.GetSize() - 1);
		subcases++;
	}
	SUBCASE("If there are N elements, where 1 < N < capacity.")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout << "Adding the three(more than 1, less than capacity) elements in the queue, then using PopFront() to pop one: \n";
		deq.PushFront(10);
		deq.PushFront(15);
		deq.PushFront(20);
		deq.PushFront(25);
		deq.PushFront(30);
		deq.PushFront(35);
		deq.PushFront(40);
		CHECK_EQ(deq.GetStartIndex(), 6);
		deq.PopFront();
		CHECK_EQ(deq.Back(), 10);
		CHECK_EQ(deq.Front(), 35);
		CHECK_EQ(deq.GetStartIndex(), 7);
		subcases++;
	}
	std::cout << std::endl;
}

TEST_CASE("Testing PopBack() function.")
{
	std::cout << "Test case 5 - PopBack():\n";
	Dequeue<int> deq;
	static int subcases = 1;
	SUBCASE("If we pop in an empty queue.")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout << "Popping when the queue is empty:\n";
		CHECK_THROWS(deq.PopBack());
		subcases++;
	}
	SUBCASE("If the startIndex points to the beginning of the queue and we pop an element.")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout << "Adding elements in a way that endIndex points to the beginning of the queue then popping the back element: \n";
		deq.PushFront(1);
		deq.PushFront(2);
		CHECK_EQ(deq.GetEndIndex(), 0);
		deq.PopBack();
		CHECK_EQ(deq.GetEndIndex(), deq.GetCapacity() - 1);
		CHECK_EQ(deq.GetEndIndex(), deq.GetStartIndex());
		subcases++;
	}
	SUBCASE("If the the size of the queue is equal to capacity / 2 and we need to resize downwards.")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout << "Adding capacity + 1 elements, then popping one with PopBack():\n";
		deq.PushBack(1);
		deq.PushBack(2);
		deq.PushBack(3);
		deq.PushBack(4);
		deq.PushBack(5);
		CHECK_EQ(deq.GetCapacity(), 8);
		deq.PopBack();

		CHECK_EQ(deq.Front(), 1);
		CHECK_EQ(deq.Back(), 4);
		CHECK_EQ(deq.GetCapacity(), 4);
		CHECK_EQ(deq.GetSize(), 4);
		CHECK_EQ(deq.GetStartIndex(), 0);
		CHECK_EQ(deq.GetEndIndex(), deq.GetSize() - 1);
		subcases++;
	}
	SUBCASE("If there are N elements, where 1 < N < capacity.")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout << "Adding the three(more than 1, less than capacity) elements in the queue, then using PopBack() to pop one: \n";
		deq.PushBack(10);
		deq.PushBack(15);
		deq.PushBack(20);
		deq.PushBack(25);
		deq.PushBack(30);
		deq.PushBack(35);
		deq.PushBack(40);
		CHECK_EQ(deq.GetEndIndex(), 6);
		deq.PopBack();
		CHECK_EQ(deq.Back(), 35);
		CHECK_EQ(deq.Front(), 10);
		CHECK_EQ(deq.GetEndIndex(), 5);
		subcases++;
	}
	std::cout << std::endl;
}

TEST_CASE("Testing Front() function.")
{
	std::cout << "Test case 6 - Front():\n";
	static int subcases = 1;
	Dequeue<int> deq;
	SUBCASE("When queue is empty.")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout << "Checking the front element when the queue is empty:\n";
		CHECK_THROWS(deq.Front());
		subcases++;
	}
	SUBCASE("When we have at least one element")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout << "Pushing some elements and getting the front one\n";
		deq.PushBack(1);
		deq.PushBack(2);
		deq.PushFront(3);
		deq.PushFront(4);
		CHECK_EQ(deq.Front(), 4);
		subcases++;
	}
	std::cout << std::endl;
}

TEST_CASE("Testing Back() function.")
{
	std::cout << "Test case 7 - Back():\n";
	static int subcases = 1;
	Dequeue<int> deq;
	SUBCASE("When queue is empty.")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout << "Checking the front element when the queue is empty:\n";
		CHECK_THROWS(deq.Back());
		subcases++;
	}
	SUBCASE("When we have at least one element.")
	{
		std::cout << "Test subcase: " << subcases << std::endl;
		std::cout << "Pushing some elements and getting the front one.\n";
		deq.PushBack(1);
		deq.PushBack(2);
		deq.PushFront(3);
		deq.PushFront(4);
		CHECK_EQ(deq.Back(), 2);
		subcases++;
	}
	std::cout << std::endl;
}