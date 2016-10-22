#ifndef __FUNCS_HPP__
#define __FUNCS_HPP__

#include "Point2D.hpp"
#include "Vec2D.hpp"
	
double dist(Point2D a, Point2D b);
double fdist(Point2D a, Point2D b);
double length(Vec2D v);
Vec2D normalize(Vec2D v);
Vec2D vectorMultiply(double scal, Vec2D vec);
Vec2D createVector(Point2D a, Point2D b);
Point2D movePoint(Point2D p, Vec2D v);

#endif
