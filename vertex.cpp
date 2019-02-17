#include"Vertex.h"

template<class type> Vertex<type>::Vertex(type val)
{
	value = val;
}
template<class type> Vertex<type>& Vertex<type>::operator=(const Vertex<type>& other)
{
	if (this == &other)
	{
		return *this;
	}
	else
	{
		this->value = other.value;
	}
	return *this;
}
template<class type> bool Vertex<type>::operator==(const Vertex<type>& other)
{
	return this->value == other.value;
}