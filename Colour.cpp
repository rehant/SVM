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
	return r/255; // OpenGL r
}

float Colour::getG()
{
	return g/255; // OpenGL g
}

float Colour::getB()
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

void Colour::setR(float nr)
{
	r = nr;
}

void Colour::setG(float ng)
{
	g = ng;
}

void Colour::setB(float nb)
{
	b = nb;
}
