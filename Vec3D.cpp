#include "Vec3D.hpp"

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

Vec3D::Vec3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
