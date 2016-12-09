#include "Point2D.hpp" // Class definition

/**
* Constructs a Point2D with the given X, Y, Z->
**/
Point2D::Point2D(float x, float y)
{
        this->x = x;
        this->y = y;
}

float Point2D::getX()
{
	return x;
}

float Point2D::getY()
{
	return y;
}

Point2D::Point2D()
{
	x = 0;
	y = 0;
}
