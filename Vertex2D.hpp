#ifndef VERTEX2D_H
#define VERTEX2D_H

struct Vertex2D
{
	float x, y;

	/**
	* Constructs a Vertex2D with the given X, Y, Z->
	**/
	Vertex2D(float x, float y)
	{
	        this->x = x;
	        this->y = y;
	}
};

#endif
