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
