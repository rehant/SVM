#include "Colour.hpp"

Colour::Colour()
{
	r = 0;
	g = 0;
	b = 0;
}

Colour::Colour(double nr, double ng, double nb)
{
	r = nr;
	g = ng;
	b = nb;
}

double Colour::getR()
{
	return r/255; // OpenGL r
}

double Colour::getG()
{
	return g/255; // OpenGL g
}

double Colour::getB()
{
	return b/255; // OpenGL b
}

Colour::Colour(Colour& other) // Copy constructor
{
	// Values are multiplied by 255 to cancel out the division in the gets
	r = other.getR()*255;
	g = other.getG()*255;
	b = other.getB()*255;
}
