#include "funcs.hpp"

float dist(Point2D a, Point2D b)
{
	return sqrt(fdist(a, b));
}

float fdist(Point2D a, Point2D b)
{
	return pow(b.getX() - a.getX(), 2) + pow(b.getY() - a.getY(), 2);
}

float length(Vec2D v)
{
	return sqrt(powf(v.getX(), 2) + powf(v.getY(), 2));
}

Vec2D normalize(Vec2D v)
{
	float vlen = length(v);
	return Vec2D(v.getX()/vlen, v.getY()/vlen, 1);
}

Vec2D vectorMultiply(float scal, Vec2D vec)
{
	return Vec2D(vec.getX()*scal, vec.getY()*scal, vec.getMagnitude());
}

Vec2D createVector(Point2D a, Point2D b)
{
	return Vec2D(b.getX() - a.getX(), b.getY() - a.getY(), dist(a, b));	
}

Point2D movePoint(Point2D p, Vec2D v)
{
	return Point2D(p.getX() + v.getX(), p.getY() + v.getY());
}
