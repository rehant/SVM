#ifndef __COLOUR_HPP__
#define __COLOUR_HPP__

class Colour
{
	private:
		double r;
		double g;
		double b;

	public:
		Colour();
		Colour(double nr, double ng, double nb);
		Colour(Colour& other); // Copy constructor
		double getR();
		double getG();
		double getB();
};

#endif
