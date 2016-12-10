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

float Camera::getPosX()
{
	return pos->getX();
}

float Camera::getPosY()
{
	return pos->getY();
}

float Camera::getPosZ()
{
	return pos->getZ();
}

float Camera::getUpX()
{
	return up->getX();
}

float Camera::getUpY()
{
	return up->getY();
}

float Camera::getUpZ()
{
	return up->getZ();
}

float Camera::getTargX()
{
	return target->getX();
}

float Camera::getTargY()
{
	return target->getY();
}

float Camera::getTargZ()
{
	return target->getZ();
}

