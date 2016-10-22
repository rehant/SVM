#ifndef __POINT2D_HPP__
#define __POINT2D_HPP__

class Point2D
{
	private:
		float x;
		float y;

	public:
		Point2D();
		Point2D(float nx, float ny);
		float getX();
		float getY();
};

#endif
