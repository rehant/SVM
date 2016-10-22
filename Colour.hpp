#ifndef __COLOUR_HPP__
#define __COLOUR_HPP__

class Colour
{
	private:
		float r;
		float g;
		float b;

	public:
		Colour();
		Colour(float nr, float ng, float nb);
		float getR();
		float getG();
		float getB();
};

#endif
