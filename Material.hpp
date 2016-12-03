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
		std::string getName();
		Material(Colour amb, Colour dif, Colour spec, std::string name);
		~Material();
		void setAmb(Colour newAmb);
		void setDif(Colour newDif);
		void setSpec(Colour newSpec);

	private:
		Colour* amb; // Ambient colour
		Colour* dif; // Diffuse colour
		Colour* spec; // Specular colour
		std::string* name;
};

#endif
