#ifndef __VEC2D_HPP__
#define __VEC2D_HPP__

class Vec2D
{
	private:
		float x;
		float y;
		float magnitude;
	
	public:
		Vec2D(); // Default constructor
		Vec2D(float nx, float ny, float mag); // Constructs Vec2D w/ specified vals
		float getX();
		float getY();
		float getMagnitude();
};

#endif
