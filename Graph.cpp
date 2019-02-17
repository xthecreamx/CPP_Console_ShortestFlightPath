#include"Graph.h"

template<class type> Graph<type>::Graph()
{ 
	numVertex = 0;
	maxVertices = 50;
	vertices = new type[maxVertices];
	marks = new bool[maxVertices];
}
template<class type> Graph<type>::Graph(int max)
{
	numVertex = 0;
	maxVertices = max;
	vertices = new type[maxVertices];
	marks = new bool[maxVertices];
}
template<class type> Graph<type>::~Graph()
{
	delete[] vertices;
	delete[] marks;
}
template<class type> bool Graph<type>::isFull()
{
	return numVertex == maxVertices;
}
template<class type> bool Graph<type>::isEmpty()
{
	return numVertex == 0;
}
template<class type> void Graph<type>::makeEmpty()
{
	numVertex = 0;
}
template<class type> void Graph<type>::addVertex(type vertex)
{
	const int NULL_EDGE = 0;

	if (!isFull())
	{
		vertices[numVertex] = vertex;

		//new vertex so no connections
		for (int i = 0; i <= numVertex; i++)
		{
			//ROW AND COLUMN REPRESENTING CORRESPONDING NEW VERTEX INDEX SET TO NULL_EDGE BECAUSE NO CONNECTIONS
			edges[numVertex][i] = NULL_EDGE;
			edges[i][numVertex] = NULL_EDGE;
		}

		numVertex++;
	}

}
template<class type> int  Graph<type>::indexIs(type vertex)
{
	int index = 0;

		while (!(vertex == vertices[index]))
		{
			index++;
		}

	return index;
}
template<class type> void Graph<type>::addEdge(type fromVertex, type toVertex, int weight)
{
	int row, column;

	row = indexIs(fromVertex);
	column = indexIs(toVertex);

	edges[row][column] = weight;
}
template<class type> void Graph<type>::getAdjacent(type fromVertex, Queue<type>& adjQueue)
{
	const int NULL_EDGE = 0;

	int row = indexIs(fromVertex);
	for (int index = 0; index < numVertex; index++)
	{
		if (edges[row][index] != NULL_EDGE)
			adjQueue.Enqueue(vertices[index]);
	}
}
template<class type> int Graph<type>::weightIs(type fromVertex, type toVertex)
{
	int row, column;

	row = indexIs(fromVertex);
	column = indexIs(toVertex);

	return edges[row][column];
}
template<class type> bool Graph<type>::isMarked(type vertex)
{
	return (marks[(indexIs(vertex))]);
}
template<class type> void Graph<type>::markVertex(type vertex)
{
	marks[(indexIs(vertex))] = true;
}
template<class type> void Graph<type>::clearMarks()
{
	for (int i = 0; i < numVertex; i++)
		marks[i] = false;
}