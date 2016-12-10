#include "Camera.hpp" // Class definition

Camera::Camera(Point3D pos, Point3D target, Vec3D up)
{
	/* Copy stuff */
	this->pos = new Point3D(pos); // Copy position
	this->target = new Point3D(target); // Copy target position
	this->up = new Vec3D(up); // Copy up vector
}

Camera::~Camera()
{
	delete up;
	delete target;
	delete pos;
}
