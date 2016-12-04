#ifndef VERTEX2D_HPP
#define VERTEX2D_HPP

class Vertex2D
{
	public:	
		/**
		* Constructs a Vertex2D with the given X, Y, Z->
		**/
		Vertex2D(float x, float y);
		float getX();
		float getY();

	private:
		float x, y;
};

#endif
