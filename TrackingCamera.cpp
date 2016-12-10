#include "TrackingCamera.hpp"

#include <iostream>
using namespace std;

TrackingCamera::TrackingCamera(Point3D pos, Player* p, Vec3D up) : Camera(pos, Point3D(p->getX(), 50, p->getZ()), up) // Construct parent
{
	this->p = p; // Store the pointer to the player for later use
	//dVec = new Vec3D(p->getX()-pos.getX(), 0-pos.getY(), p->getZ()-pos.getZ()); // Create the Vec3D from our position to the player
	dVec = new Vec3D(pos.getX()-p->getX(), pos.getY(), pos.getZ()-p->getZ());
	/*cout << "TrackingCamera::TrackingCamera: Player pos (X, Z) = (" << p->getX() << ", " << p->getZ() << ")" << endl
	<< "\tCamera pos (X, Y, Z) = (" << pos.getX() << ", " << pos.getY() << ", " << pos.getZ() << ")" << endl
	<< "\tVector (X, Y, Z) = (" << dVec->getX() << ", " << dVec->getY() << ", " << dVec->getZ() << ")" << endl;*/
}

/**
* Updates position to track player
*/
void TrackingCamera::update()
{
	delete pos; // Delete our old position
	
	/* Calculate our new position based on the distance to be maintained */
	Point3D pPos(p->getX(), 0, p->getZ()); // Player position
	//cout << "TrackingCamera::update: player position = (" << pPos.getX() << ", " << pPos.getY() << ", " << pPos.getZ() << ")" << endl;
	pos = new Point3D(movePoint(pPos, *dVec)); // Our position is the player's position moved along the initial vector
	//cout << "TrackingCamera::update: new position = (" << pos->getX() << ", " << pos->getY() << ", " << pos->getZ() << ")" << endl;
	
	/* Change target to new position */
	delete target;
	target = new Point3D(p->getX(), 50, p->getZ()); // Set new target
}

TrackingCamera::~TrackingCamera()
{
	delete dVec; // Delete distance vector
}

void TrackingCamera::move(float xAmt, float yAmt, float zAmt)
{
	/* Move position */
	pos->setX(pos->getX()+xAmt);
	pos->setY(pos->getY()+yAmt);
	pos->setZ(pos->getZ()+zAmt);
}
