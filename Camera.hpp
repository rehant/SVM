#ifndef __CAMERA_HPP__
#define __CAMERA_HPP_

#include "Point3D.hpp"
#include "Vec3D.hpp"

class Camera // Camera with a fixed target
{
	public:
		Camera(Point3D pos, Point3D target, Vec3D up);
		~Camera();

	protected:
		Point3D* pos; // Position
		Point3D* target; // Target
		Vec3D* up; // Up vector
};

#endif
