#include "Vec3D.hpp"
#include <cmath> // sqrt

/**
* Constructor. Creates a Vec3D containing X, Y, Z vals.
* \param x X coord
* \param y Y coord
* \param z Z coord
*/
Vec3D::Vec3D(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->mag = sqrt(x*x+y*y+z*z);
}

Vec3D::~Vec3D()
{
    //dtor
}

Vec3D::Vec3D(const Vec3D& other)
{
    this->x = other.getX();
    this->y = other.getY();
    this->z = other.getZ();
}

Vec3D& Vec3D::operator=(const Vec3D& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
