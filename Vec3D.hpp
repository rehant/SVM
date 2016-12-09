#ifndef VEC3D_HPP
#define VEC3D_HPP

class Vec3D
{
	private:
		float x, y, z;

	public:
		/**
		* Constructs a Vec3D with the given X, Y, Z.
		**/
		Vec3D(float &x, float &y, float &z);
		Vec3D(float x, float y, float z);
		Vec3D();
		float getX();
		float getY();
		float getZ();
};

#endif
