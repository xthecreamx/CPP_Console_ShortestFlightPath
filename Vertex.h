#ifndef VERTEX_DEFINED
#define VERTEX_DEFINED

#include<iostream>

template<class type>
class Vertex
{
private:
	type value;
public:
	Vertex() {};
	Vertex(type);
	Vertex<type>& operator=(const Vertex<type>&);
	bool operator==(const Vertex<type>&);
	friend std::ostream& operator<<(std::ostream& out, const Vertex<type>& vertex);
};

#include"Vertex.cpp"

#endif
