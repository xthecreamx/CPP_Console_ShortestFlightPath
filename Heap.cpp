#include"Heap.h"

template<class type> void Heap<type>::Swap(type& x, type& y)
{
	type temp = x;
	x = y;
	y = temp;
}
template<class type> void Heap<type>::ReHeapDown(int root, int bottom)
{
	int minChild, leftChild, rightChild; //positions that represent a Node's links

	leftChild = (root * 2) + 1;
	rightChild = (root * 2) + 2;

	if (leftChild <= bottom) // if leftChild is greater than bottom then Node is a leaf.
	{
		if (leftChild == bottom) // if leftChild is bottom then Node has 1 child that is a left because of the shape property
		{
			minChild = leftChild;
		}
		else
		{
			if (elements[leftChild] >= elements[rightChild]) //<= means max heap 
			{
				minChild = rightChild;
			}
			else
			{
				minChild = leftChild;
			}

			if (elements[root] > elements[minChild]) // swap values only if value property is violated NOTE: < means max heap
			{
				Swap(elements[root], elements[minChild]);
				ReHeapDown(minChild, bottom);
			}
		}
	}


}

template<class type> void Heap<type>::ReHeapUp(int root, int bottom)
{
	int parent;

	if (bottom > root) // as long as the Node is not the root 
	{
		parent = (bottom - 1) / 2;//Equation for parent Node 

		if (elements[parent] > elements[bottom]) //Violation of order property  NOTE:< is max heap
		{
			Swap(elements[parent], elements[bottom]);
			ReHeapUp(root, parent);
		}
	}
}
