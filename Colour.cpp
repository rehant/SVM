#include "Colour.hpp"

Colour::Colour()
{
	r = 0;
	g = 0;
	b = 0;
}

Colour::Colour(float nr, float ng, float nb)
{
	r = nr;
	g = ng;
	b = nb;
}

float Colour::getR()
{
	return r;
}

float Colour::getG()
{
	return g;
}

float Colour::getB()
{
	return b;
}
