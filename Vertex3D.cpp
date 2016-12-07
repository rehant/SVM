#include "Vertex3D.hpp"

/**
* Constructs a Vertex3D with the given X, Y, Z.
**/
Vertex3D::Vertex3D(float &x, float &y, float &z)
{
        this->x = x;
        this->y = y;
        this->z = z;
}

float Vertex3D::getX()
{
	return x;
}

float Vertex3D::getY()
{
	return y;
}

float Vertex3D::getZ()
{
	return z;
}

Vertex3D::Vertex3D()
{
	x = 0;
	y = 0;
	z = 0;
}
