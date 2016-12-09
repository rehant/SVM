#include "Vec3D.hpp"

/**
* Constructs a Vec3D with the given X, Y, Z.
**/
Vec3D::Vec3D(float &x, float &y, float &z)
{
        this->x = x;
        this->y = y;
        this->z = z;
}

float Vec3D::getX()
{
	return x;
}

float Vec3D::getY()
{
	return y;
}

float Vec3D::getZ()
{
	return z;
}

Vec3D::Vec3D()
{
	x = 0;
	y = 0;
	z = 0;
}
