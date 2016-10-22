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
	return r;
}

double Colour::getG()
{
	return g;
}

double Colour::getB()
{
	return b;
}
