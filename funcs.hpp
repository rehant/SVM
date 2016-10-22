#ifndef __FUNCS_HPP__
#define __FUNCS_HPP__

// C library includes
#include <cmath> // sqrt, pow

// Our includes
#include "Point2D.hpp"
#include "Vec2D.hpp"
	
float dist(Point2D a, Point2D b);
float fdist(Point2D a, Point2D b);
float length(Vec2D v);
Vec2D normalize(Vec2D v);
Vec2D vectorMultiply(float scal, Vec2D vec);
Vec2D createVector(Point2D a, Point2D b);
Point2D movePoint(Point2D p, Vec2D v);

#endif
