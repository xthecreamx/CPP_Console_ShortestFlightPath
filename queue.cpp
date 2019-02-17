template<class type> Queue<type>::Queue()
{
	numElements = 0;
	maxElements = 50;
	elements = new type[maxElements];
}
template<class type> Queue<type>::Queue(int max)
{
	numElements = 0;
	maxElements = max;
	elements = new type[maxElements];
}
template<class type> Queue<type>::~Queue()
{
	delete[] elements;
}
template<class type> void Queue<type>::makeEmpty()
{
	numElements = 0;
}
template<class type> void Queue<type>::Enqueue(type item)
{
	if(!isFull())
	elements[numElements++] = item;
}
template<class type> void Queue<type>::Dequeue(type& itemLocation)
{
	if (!isEmpty())
	{
		itemLocation = elements[0];
		numElements--;
		for (int index = 0; index < numElements; index++)
		{ 
			elements[index] = elements[index + 1];
		}
	}
}
template<class type> bool Queue<type>::isFull()
{
	return numElements == maxElements;
}
template<class type> bool Queue<type>::isEmpty()
{
	return numElements == 0;
}