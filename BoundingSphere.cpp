#include "BoundingSphere.hpp" // Class definition
#include <iostream>
using namespace std; 

/* My includes */
#include "funcs.hpp" // dist, fdist

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
	double sqDist = fdist(Point3D(x, y, z), other.getCentre()); // Get squared distance between sphere centres
	double sqRadSum = (rad+other.getRadius())*(rad+other.getRadius()); // Squared sum of both radii
	
	if (sqDist <= sqRadSum) // Collision occurred
	{
		cout << "success";
		return true;
	}
	cout << "no success";
	return false;
}

Point3D BoundingSphere::getCentre()
{
	return *centre;
}

float BoundingSphere::getX()
{
	return x;
}

float BoundingSphere::getY()
{
	return y;
}

float BoundingSphere::getZ()
{
	return z;
}

double BoundingSphere::getRadius()
{
	return rad;
}

BoundingSphere::BoundingSphere(Mesh m) // Create bounding sphere based on a mesh
{
	/*
	* ALGORITHM
	* ---------
	* Initialize 2 furthest points (p1, p2) and maximum distance (diameter)
	* 
	* For every point in the mesh as a:
	*	For every point in the mesh as b:
	*		curDist = distance(a, b) # Find distance between points
	*		
	*		if curDist > diameter: # Distance between these 2 points is greater than maximum distance
	*			p1, p2 = a, b # Store the points
	*			diameter = curDist # Store the new maximum distance
	*
	* double radius = diameter / 2
	* Point3D midpoint = ((p1.x+p2.x)/2, (p1.y+p2.y)/2, (p1.z+p2.z)/2) # Find the midpoint of the line (sphere's centre)
	* bsp = new BoundingSphere(midpoint, radius) // Create the bounding sphere
	*/

	double diam = 0.0; // Sphere diameter
	double curRad = 0.0; // Radius between 2 points currently being checked
	int p1Ind = 0;
	int p2Ind = 0;
	vector<Point3D> verts = m.getVerts(); // Fetch vertices from mesh

	/* Find diamterically opposing points and sphere's diameter */
	for (int i = 0; i < verts.size(); i++) // Outer loop through vertices
	{
		for (int j = 0; j < verts.size(); j++) // Inner loop through vertices
		{
			curRad = dist(verts.at(i), verts.at(j)); // Find the distance between the 2 points	

			if (curRad > diam) // Distance between current 2 points > current diameter, need to update
			{
				p1Ind = i; // Store index of first point
				p2Ind = j; // Store index of second point
				diam = curRad; // Update diameter
			}
		}
	}

	rad = diam / 2; // Store sphere radius
	Point3D p1 = verts.at(p1Ind); // Fetch first point on diameter
	Point3D p2 = verts.at(p2Ind); // Fetch second point on diameter
	this->x = (p1.getX()+p2.getX())/2;
	this->y = (p1.getY()+p2.getY())/2;
	this->z = (p1.getZ()+p2.getZ())/2; // Midpoint (centre point of sphere)
}

BoundingSphere::BoundingSphere(float posX, float posY, float posZ, float size)
{	
	float diam = size;
	rad = diam/2;
	this->x = posX;
	this->y = posY;
	this->z = posZ;
}
