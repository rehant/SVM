#include "BoundingBox.hpp"

bool BoundingBox::isCollidingWith(BoundingBox other)
{
	/* TODO */
	return true;
}

BoundingBox::~BoundingBox()
{
	delete topBackLeft;
	delete topBackRight;
	delete topFrontLeft;
	delete topFrontRight;
	delete bottomBackLeft;
	delete bottomBackRight;
	delete bottomFrontLeft;
	delete bottomFrontRight;
}

BoundingBox::BoundingBox(Point3D bbl, Point3D tfr)
{
	/* The easy part */
	this->bottomBackLeft = new Point3D(bbl);
	this->topFrontRight = new Point3D(tfr);

	/* Calcuolate distances */
	float mXD = topFrontRight->getX() - bottomBackLeft->getX(); // Max x distance
	float mYD = topFrontRight->getY() - bottomBackLeft->getY(); // Max y dist
	float mZD = topFrontRight->getZ() - bottomBackLeft->getZ(); // Max z dist

	this->topBackLeft = new Point3D(bottomBackLeft->getX(), bottomBackLeft->getY()+mYD, bottomBackLeft->getZ()); // Just above bottom back left
	this->topBackRight = new Point3D(topFrontRight->getX(), topFrontRight->getY(), topFrontRight->getZ()-mZD); // Behind top back right
	this->topFrontLeft = new Point3D(topFrontRight->getX()-mXD, topFrontRight->getY(), topFrontRight->getZ()); // To left of top front right
	this->bottomBackRight = new Point3D(topBackRight->getX(), topBackRight->getY()-mYD, topBackRight->getZ()); // Below on y axis than top back right
	this->bottomFrontLeft = new Point3D(bottomBackLeft->getX(), bottomBackLeft->getY(), bottomBackLeft->getZ()+mZD); // Further forward on z axis than bottom back left
	this->bottomFrontRight = new Point3D(bottomFrontLeft->getX()+mXD, bottomFrontLeft->getY(), bottomFrontLeft->getZ()); // Further right on x axis than bottom front left
}
