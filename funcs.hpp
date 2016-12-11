#ifndef __FUNCS_HPP__
#define __FUNCS_HPP__

#include "Point2D.hpp"
#include "Vec3D.hpp"
#include "Point3D.hpp"

double dist(Point3D a, Point3D b);
double fdist(Point3D a, Point3D b);
double length(Vec3D v);
Vec3D normalize(Vec3D v);
Vec3D vectorMultiply(double scal, Vec3D vec);
Vec3D createVector(Point3D a, Point3D b);
Point3D movePoint(Point3D p, Vec3D v);
int randIntInRange(int lbound, int ubound);
Point3D randomPointOnLine(Point3D left, Point3D right); // Returns a random point on a 2D line
double dist(Point3D a, Point3D b);
double fdist(Point3D a, Point3D b);
Vec3D cross(Vec3D u, Vec3D v); // Cross-product
Vec3D avg(Vec3D vecs[], int nVecs); // Averages $nVecs vectors and returns the result
Vec3D quadNormal(Point3D p1, Point3D p2, Point3D p3, Point3D p4); // Calculates the normal for a quad defined by the given points (assumed to be in counter-clockwise order)
Vec3D triNormal(Point3D p1, Point3D p2, Point3D p3); // Calculates and returns the normal for a triangle
double unsquaredDist(float ax, float ay, float az, float bx, float by, float bz);

#endif
