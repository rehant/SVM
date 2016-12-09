#ifndef POINT2D_HPP
#define POINT2D_HPP

class Point2D
{
	public:	
		/**
		* Constructs a Point2D with the given X, Y, Z->
		**/
		Point2D(float x, float y);
		float getX();
		float getY();
		Point2D();

	private:
		float x, y;
};

#endif
