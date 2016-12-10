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
		Colour(Colour& other); // Copy constructor
		float getR();
		float getG();
		float getB();
		void setR(float nr);
		void setG(float ng);
		void setB(float nb);
};

#endif
