#ifndef VERTEX3D_HPP
#define VERTEX3D_HPP

class Vertex3D
{
	private:
		float x, y, z;

	public:
		/**
		* Constructs a Vertex3D with the given X, Y, Z.
		**/
		Vertex3D(float &x, float &y, float &z);
		float getX();
		float getY();
		float getZ();
		Vertex3D();
};

#endif
