#include "Face3D.hpp"
#include "Vec3D.hpp"
#include <vector>
#include <string>
#include <iostream>

/**
* Constructs a Face3D with vertex, vertex texture, normal vector indices and material ids
**/
Face3D::Face3D(int v1, int v2, int v3, int t1, int t2, int t3, int n1, int n2, int n3, std::string mat_id)
{
	// Vertex indices
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;

	// Texture indices
	this->t1 = t1;
	this->t2 = t2;
	this->t3 = t3;

	// Normal indices
	this->n1 = n1;
	this->n2 = n2;
	this->n3 = n3;

	// Identifier for current material
	this->mat_id = mat_id;

//	std::cout << "Vertices = " << v1 << ", " << v2 << ", " << v3 << "; Texture vertices = " << t1 << ", " << t2 << ", " << t3 << "; " << "Normal = (" << n1 << ", " << n2 << ", " << n3 <<")" << std::endl;
}


// Index of v1
int Face3D::getV1()
{
	return v1;
}

// Index of v2
int Face3D::getV2()
{
	return v2;
}

// Index of v3
int Face3D::getV3()
{
	return v3;
}

// Index of t1
int Face3D::getT1()
{
	return t1;
}

// Index of t2
int Face3D::getT2()
{
	return t2;
}

// Index of t3
int Face3D::getT3()
{
	return t3;
}

// Index of n1
int Face3D::getN1()
{
	return n1;
}

// Index of n2
int Face3D::getN2()
{
	return n2;
}

// Index of n3
int Face3D::getN3()
{
	return n3;
}

// Material id of face
std::string Face3D::getMatID()
{
	return mat_id;
}
