#ifndef VERTEX3D_H
#define VERTEX3D_H

struct Vertex3D
{
	float x, y, z;

	/**
	* Constructs a Vertex3D with the given X, Y, Z.
	**/
	Vertex3D(float x, float y, float z)
	{
        this.x = x;
        this.y = y;
        this.z = z;
	}
};

#endif
