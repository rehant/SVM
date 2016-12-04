#ifndef MATERIAL_HPP
#define MATERIAL_HPP

// STL includes
#include <string>

// My includes
#include "Colour.hpp" // Colour

class Material
{
	public:
		Colour getAmb() const;
		Colour getDif() const;
		Colour getSpec() const;
		std::string getName() const;
		Material(Colour amb, Colour dif, Colour spec, int shine, std::string name);
		~Material();
		void setAmb(Colour newAmb);
		void setDif(Colour newDif);
		void setSpec(Colour newSpec);
		void setName(std::string newname);
		int getShine() const;
		Material();
		Material(float ambR, float ambG, float ambB, float difR, float difG, float difB, float specR, float specG, float specB, int shine, std::string name);
		Material(const Material& other);

	private:
		Colour* amb; // Ambient colour
		Colour* dif; // Diffuse colour
		Colour* spec; // Specular colour
		std::string* name;
		int shine;
};

#endif
