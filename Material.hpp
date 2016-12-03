#ifndef MATERIAL_HPP
#define MATERIAL_HPP

// STL includes
#include <string>

// My includes
#include "Colour.hpp" // Colour

class Material
{
	public:
		Colour getAmb();
		Colour getDif();
		Colour getSpec();
		string getName();

	private:
		Colour amb; // Ambient colour
		Colour dif; // Diffuse colour
		Colour spec; // Specular colour
		string name;
};

#endif
