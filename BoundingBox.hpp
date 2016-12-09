#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include "Point3D.hpp"

class BoundingBox
{
	public:
		BoundingBox(Point3D bbl, Point3D tfr);
		bool isCollidingWith(BoundingBox other);
		~BoundingBox();

	private:
		Point3D* topBackLeft;
		Point3D* topBackRight;
		Point3D* topFrontLeft;
		Point3D* topFrontRight;
		Point3D* bottomBackLeft;
		Point3D* bottomBackRight;
		Point3D* bottomFrontLeft;
		Point3D* bottomFrontRight;
};

#endif
