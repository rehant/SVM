#ifndef __CAMERA_HPP__
#define __CAMERA_HPP_

#include "Point3D.hpp"
#include "Vec3D.hpp"

class Camera // Camera with a fixed target
{
	public:
		Camera(Point3D pos, Point3D target, Vec3D up);
		~Camera();

		/** Getters **/
		float getPosX();
		float getPosY();
		float getPosZ();
		float getUpX();
		float getUpY();
		float getUpZ();
		float getTargX();
		float getTargY();
		float getTargZ();

	protected:
		Point3D* pos; // Position
		Point3D* target; // Target
		Vec3D* up; // Up vector
};

#endif
