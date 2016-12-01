#ifndef __POINT2D_HPP__
#define __POINT2D_HPP__

class Point2D
{
	private:
		double x;
		double y;

	public:
		Point2D();
		Point2D(double nx, double ny);
		double getX();
		double getY();
		void setX(double newX);
		void setY(double newY);
};

#endif
