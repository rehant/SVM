#ifndef POINT3D_HPP
#define POINT3D_HPP

class Point3D
{
	private:
		float x, y, z;

	public:
		/**
		* Constructs a Point3D with the given X, Y, Z.
		**/
		Point3D(float x, float y, float z);
		float getX() const;
		float getY() const;
		float getZ() const;
		Point3D();
		Point3D(const Point3D& other);
};

#endif
