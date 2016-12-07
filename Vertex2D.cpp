#include "Vertex2D.hpp" // Class definition

/**
* Constructs a Vertex2D with the given X, Y, Z->
**/
Vertex2D::Vertex2D(float x, float y)
{
        this->x = x;
        this->y = y;
}

float Vertex2D::getX()
{
	return x;
}

float Vertex2D::getY()
{
	return y;
}

Vertex2D::Vertex2D()
{
	x = 0;
	y = 0;
}
