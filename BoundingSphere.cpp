#include "BoundingSphere.hpp" // Class definition

BoundingSphere::BoundingSphere(Mesh m) //
{
}

BoundingSphere::BoundingSphere(Point3D c, double r)
{
	/* Copy values */
	centre = new Point3D(c); // Copy centre
	rad = r; // Copy radius
}

BoundingSphere::~BoundingSphere()
{
	delete centre;
}

bool BoundingSphere::collidingWith(BoundingSphere other) // Whether or not this bounding sphere is colliding with another bounding sphere
{
	double sqDist = fdist(*centre, other.getCentre()); // Get squared distance between sphere centres
	double sqRadSum = (rad+other.getRadius())*(rad+other.getRadius()); // Squared sum of both radii
	
	if (sqDist <= sqRadSum) // Collision occurred
	{
		return true;
	}

	return false;
}

Point3D BoundingSphere::getCentre()
{
	return *centre;
}

double getRadius()
{
	return rad;
}
