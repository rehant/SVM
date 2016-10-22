#ifndef __VEC2D_HPP__
#define __VEC2D_HPP__

class Vec2D
{
	private:
		double x;
		double y;
		double magnitude;
	
	public:
		Vec2D(); // Default constructor
		Vec2D(double nx, double ny, double mag); // Constructs Vec2D w/ specified vals
		double getX();
		double getY();
		double getMagnitude();
};

#endif
