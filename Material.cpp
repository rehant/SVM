#include "Material.hpp"

Colour Material::getAmb()
{
	return *amb;
}

Colour Material::getDif()
{
	return *dif;
}

Colour Material::getSpec()
{
	return *spec;
}

std::string Material::getName()
{
	return *name;
}

Material::Material(Colour amb, Colour dif, Colour spec, int shine, std::string name)
{
	/* Copy stuff */
	this->amb = new Colour(amb.getR()*255, amb.getG()*255, amb.getB()*255);
	this->dif = new Colour(dif);
	this->spec = new Colour(spec);
	this->name = new std::string(name);
	this->shine = shine;
}

Material::~Material()
{
	delete amb;
	delete dif;
	delete spec;
	delete name;
}

void Material::setAmb(Colour newAmb)
{
	delete amb; // Destroy current amber colour
	amb = new Colour(newAmb); // Copy the colour
}

void Material::setDif(Colour newDif)
{
	delete dif;
	dif = new Colour(newDif);
}

void Material::setSpec(Colour newSpec)
{
	delete spec;
	spec = new Colour(newSpec);
}

int Material::getShine()
{
	return shine;
}
