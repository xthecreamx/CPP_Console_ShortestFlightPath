#ifndef QUEUE_DEFINED
#define QUEUE_DEFINED

//Array-based Queue 

template<class type>
class Queue
{
private:
	int numElements;
	int maxElements;
	type * elements;
public:
	Queue();
	Queue(int);
	~Queue();
	void makeEmpty();
	void Enqueue(type);
	void Dequeue(type&);
	bool isFull();
	bool isEmpty();
};

#include"queue.cpp"

#endif
