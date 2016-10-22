/* C++ Implementation of Point2D class */
#include "Point2D.hpp" // Class definition

/**
*	Default constructor. Initializes vars to 0.
*/
Point2D::Point2D()
{
	x = 0;
	y = 0;
}

/**
*	Constructs a Point2D with the given (x, y) vals.
*/
Point2D::Point2D(double nx, double ny)
{
	/* Store vals */
	x = nx;
	y = ny;
}

double Point2D::getX()
{
	return x;
}

double Point2D::getY()
{
	return y;
}
