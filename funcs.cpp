#include "funcs.hpp"
#include <cmath> // sqrt, pow, powf,
#include <cstdlib> // rand()
#include <ctime> // time()
#include <iostream>

double dist(Point3D a, Point3D b) // 3D distance
{
	return sqrt(fdist(a, b));
}

double fdist(Point3D a, Point3D b) // 3D unrooted distance
{
	return pow(b.getX() - a.getX(), 2) + pow(b.getY() - a.getY(), 2) + pow(b.getZ() - a.getZ(), 2);
}

double length(Vec3D v)
{
	return sqrt(powf(v.getX(), 2) + powf(v.getY(), 2) + powf(v.getZ(), 2));
}

Vec3D normalize(Vec3D v)
{
	double vlen = length(v);
	return Vec3D(v.getX()/vlen, v.getY()/vlen, v.getZ()/vlen);
}

Vec3D vectorMultiply(double scal, Vec3D vec)
{
	return Vec3D(vec.getX()*scal, vec.getY()*scal, vec.getZ()*scal);
}

Vec3D createVector(Point3D a, Point3D b)
{
	return Vec3D(b.getX() - a.getX(), b.getY() - a.getY(), b.getZ() - a.getZ());
}

Point3D movePoint(Point3D p, Vec3D v)
{
	return Point3D(p.getX() + v.getX(), p.getY() + v.getY(), p.getZ() + v.getZ());
}

int randIntInRange(int lbound, int ubound)
{
    srand(time(NULL)); // Seed RNG with current time
    int range = ubound - lbound; // Range of numbers to be added to lbound
    int toAdd = rand() % range; // Choose a random number in the range of possible differences
    return lbound + toAdd; // Return a random number in the range [lbound, ubound]
}

Point2D randomPointOnLine(Point2D left, Point2D right) // Returns a random point on a 2D line
{
    double slope = (right.getY()-left.getY()) / (right.getX() - left.getX());
    double yIntercept = right.getY() - slope * right.getX();
    double randX; // x value on line to use

    if (left.getX() <= right.getX()) // Left point is actually to left
    {
        randX = (double)randIntInRange(left.getX(), right.getX()); // Store random x
    }

    else // "Right" point is further left
    {
          randX = (double)randIntInRange(right.getX(), left.getX()); // Store rando
    }

    return Point2D(randX, slope*randX+yIntercept); // Return a random point on the line
}

/**
* \desc Cross product of 2 vectors.
* \name cross
* \param u Vector 1
* \param v Vector 2
* \return The cross product of the 2 vectors.
*/
Vec3D cross(Vec3D u, Vec3D v)
{
	float u1 = u.getX();
	float u2 = u.getY();
	float u3 = u.getZ();
	float v1 = v.getX();
	float v2 = v.getY();
	float v3 = v.getZ();
	/*std::clog << "cross: x = " << u2 << "*" << v3 << " - " << u3 << " * " << v2 << "(" << u2*v3-u3*v2 << "), " << u3 << "*" << v1 << "-" << u1 << "*" << v3 << "(" << u3*v1-u1*v3
		<< "), " << u1 << "*" << v2 << "-" << u2 << "*" << v1 << " (" << u1*v2-u2*v1 << ")" << std::endl;*/
	Vec3D res(u2*v3-u3*v2, u3*v1-u1*v3, u1*v2-u2*v1);
	return res;
}

Vec3D avg(Vec3D vecs[], int nVecs)
{
    double xTot = 0; // Total of all x values
    double yTot = 0; // Total of all y values
    double zTot = 0; // Total of all z values

    for (int v = 0; v < nVecs; v++) // Loop through vector arary
    {
        /* Add current values to totals */
        xTot += vecs[v].getX();
        yTot += vecs[v].getY();
        zTot += vecs[v].getZ();
    }

    return Vec3D(xTot / nVecs, yTot / nVecs, zTot / nVecs); // Return a vector with the average of each coord
}

Vec3D quadNormal(Point3D p1, Point3D p2, Point3D p3, Point3D p4)
{
    /* Create quad sides */
    /*std::clog << "sideA = (" << p2.getX() << " - " << p1.getX() << " {" << p2.getX() - p1.getX()
    << "}, " << p2.getY() << " - " << p1.getY() << " {" << p2.getY() - p1.getY()
    << "}, " << p2.getZ() << " - " << p1.getZ() << " {" << p2.getZ() - p1.getZ() << "})"
    << std::endl;*/
    Vec3D sideA(p2.getX() - p1.getX(), p2.getY() - p1.getY(), p2.getZ() - p1.getZ());

    /*std::clog << "sideB = (" << p3.getX() << " - " << p2.getX() << " {" << p3.getX() - p2.getX()
    << "}, " << p3.getY() << " - " << p2.getY() << " {" << p3.getY() - p2.getY()
    << "}, " << p3.getZ() << " - " << p2.getZ() << " {" << p3.getZ() - p2.getZ() << "})"
    << std::endl;*/
    Vec3D sideB(p3.getX() - p2.getX(), p3.getY() - p2.getY(), p3.getZ() - p2.getZ());

    /*std::clog << "sideC = (" << p4.getX() << " - " << p3.getX() << " {" << p4.getX() - p3.getX()
    << "}, " << p4.getY() << " - " << p3.getY() << " {" << p4.getY() - p3.getY()
    << "}, " << p4.getZ() << " - " << p3.getZ() << " {" << p4.getZ() - p3.getZ() << "})"
    << std::endl;*/
    Vec3D sideC(p4.getX() - p3.getX(), p4.getY() - p3.getY(), p4.getZ() - p3.getZ());

    /*std::clog << "sideD = (" << p1.getX() << " - " << p4.getX() << " {" << p1.getX() - p4.getX()
    << "}, " << p1.getY() << " - " << p4.getY() << " {" << p1.getY() - p4.getY()
    << "}, " << p1.getZ() << " - " << p4.getZ() << " {" << p1.getZ() - p4.getZ() << "})"
    << std::endl;*/
    Vec3D sideD(p1.getX() - p4.getX(), p1.getY() - p4.getY(), p1.getZ() - p4.getZ());

    /* Create the 2 cross products */
    Vec3D norms[2]; // Array for normals (passed to average)

    norms[0] = cross(sideA, sideB); // Normal for A x B
    norms[1] = cross(sideC, sideD); // Normal for C x D

    /*std::clog << "Normal 1 = (" << norms[0].getX() << ", " << norms[0].getY() << ", " << norms[0].getZ() << "), normal 2 = (" << norms[1].getX() << ", "
    << norms[1].getY() << ", " << norms[1].getZ() << ")" << std::endl;*/

    Vec3D norm = avg(norms, 2); // Get the true normal = the average of the normals
    //std::clog << "Normal = (" << norm.getX() << ", " << norm.getY() << ", " << norm.getZ() << ")" << std::endl;

    //std::clog << "============================================================================================" << std::endl;

    return normalize(norm); // Return the quad's normal
}

Vec3D triNormal(Point3D p1, Point3D p2, Point3D p3) // Calculates and returns the normal for a triangle
{
	Vec3D side1(p2.getX() - p1.getX(), p2.getY() - p1.getY(), p2.getZ() - p1.getZ()); // Vector 1
	Vec3D side2(p3.getX() - p2.getX(), p3.getY() - p2.getY(), p3.getZ() - p2.getZ()); // Vector 2
	return cross(side1, side2); // Cross product of sides is normal
}
