#include "Point3D.hpp"

/**
* Constructs a Point3D with the given X, Y, Z.
**/
Point3D::Point3D(float x, float y, float z)
{
        this->x = x;
        this->y = y;
        this->z = z;
}

float Point3D::getX() const
{
	return x;
}

float Point3D::getY() const
{
	return y;
}

float Point3D::getZ() const
{
	return z;
}

Point3D::Point3D()
{
	x = 0;
	y = 0;
	z = 0;
}

Point3D::Point3D(const Point3D& other)
{
	this->x = other.getX();
	this->y = other.getY();
	this->z = other.getZ();
}
