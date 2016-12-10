#ifndef __BOUNDINGSPHERE_HPP__
#define __BOUNDINGSPHERE_HPP__

/* STL includes */
#include <vector>
using namespace std;

/* Our includes */
#include "Point3D.hpp"
#include "Mesh.hpp"

class BoundingSphere
{
	public:
		BoundingSphere(Point3D c, double r); // Construct a bounding sphere at the given point with the given radius
		~BoundingSphere(); // Destructor
		bool collidingWith(BoundingSphere other); // Whether or not this bounding sphere is colliding with another bounding sphere
		Point3D getCentre();
		double getRadius();
		BoundingSphere(Mesh m); // Create the bounding sphere based on the mesh
		BoundingSphere(float posX, float posY, float posZ, float size);

	private:
		Point3D* centre; // Centre point of sphere
		double rad; // Radius
};

#endif
