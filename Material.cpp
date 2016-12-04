#include "Material.hpp"

Colour Material::getAmb() const
{
	return *amb;
}

Colour Material::getDif() const
{
	return *dif;
}

Colour Material::getSpec() const
{
	return *spec;
}

std::string Material::getName() const
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

int Material::getShine() const
{
	return shine;
}

Material::Material() // Default constructor
{
	this->amb = new Colour(255, 255, 255);
	this->dif = new Colour(128, 128, 128);
	this->spec = new Colour(0, 0, 0);
	this->name = new std::string("Default");
	shine = 128;
}

void Material::setName(std::string newname)
{
	delete name;
	name = new std::string(newname); // Copy the name
}

Material::Material(float ambR, float ambG, float ambB, float difR, float difG, float difB, float specR, float specG, float specB, int shine, std::string name)
{
	this->amb = new Colour(ambR, ambG, ambB);
	this->dif = new Colour(difR, difG, difB);
	this->spec = new Colour(specR, specG, specB);
	this->name = new std::string(name);
	this->shine = shine;
}

Material::Material(const Material& other) // Copy constructor
{
	this->amb = new Colour(255*other.getAmb().getR(), 255*other.getAmb().getG(), 255*other.getAmb().getB());
	this->dif = new Colour(255*other.getDif().getR(), 255*other.getDif().getG(), 255*other.getDif().getB());
	this->spec = new Colour(255*other.getSpec().getR(), 255*other.getSpec().getG(), 255*other.getSpec().getB());
	this->name = new std::string(other.getName());
	this->shine = other.getShine();
}
