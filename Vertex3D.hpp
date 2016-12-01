#ifndef VERTEX3D_H
#define VERTEX3D_H

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
};

#endif
