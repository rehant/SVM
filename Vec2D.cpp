#include "Vec2D.hpp"

/**
*	Default constructor.
*/
Vec2D::Vec2D()
{
	x = 0;
	y = 0;
	magnitude = 0;
}

/**
*	Constructs a Vec2D w/ specified args.
*/
Vec2D::Vec2D(double nx, double ny, double mag)
{
	x = nx;
	y = ny;
	magnitude = mag;
}

double Vec2D::getX()
{
	return x;
}

double Vec2D::getY()
{
	return y;
}

double Vec2D::getMagnitude()
{
	return magnitude;
}
