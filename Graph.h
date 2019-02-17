#ifndef GRAPH_DEFINED
#define GRAPH_DEFINED

//Array based graph

#include"Queue.h"

template<class type>
class Graph
{
private:
	int numVertex;
	int maxVertices;
	int edges[50][50];
	type * vertices;
	bool * marks;
	int indexIs(type);
public:
	Graph();
	Graph(int);
	~Graph();
	bool isFull();
	bool isEmpty();
	void makeEmpty();
	void addVertex(type);
	void addEdge(type,type,int);
	void getAdjacent(type, Queue<type>&);
	int weightIs(type,type);
	bool isMarked(type);
	void markVertex(type);
	void clearMarks();
	friend void departureSelection(Graph<type>&, type&);
	friend void destinationSelection(Graph<type>&, type& , type&);
	friend void viewInfo(Graph<type>&);
};

#include"Graph.cpp"

#endif 

