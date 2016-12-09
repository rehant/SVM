#ifndef __MESH_HPP__
#define __MESH_HPP__

/* C++ STL */
#include <string>
#include <vector>
#include <map>

// My includes
#include "Colour.hpp"
#include "Point3D.hpp"
#include "Face3D.hpp"
#include "Point2D.hpp"
#include "Material.hpp"
#include "Vec3D.hpp"

class Mesh
{
    public:
        /**
        * Constructor. Loads a .OBJ file into an object.
        */
        Mesh(std::string filename);

        /**
        * Destructor. Performs cleanup when mesh is deleted.
        */
        ~Mesh();

	/**
	* Copy constructor
	*/
	Mesh(Mesh& other);

	void operator=(const Mesh& other);

	/*** Getters ***/
	std::vector<Point3D> getVerts();
	std::vector<Point2D> getTexVerts();
	std::vector<Vec3D> getNorms();
	std::map<std::string, Material> getMats();
	std::vector<Face3D> getFaces();
	Material getMaterial(std::string name);

    private:
    	void loadMats(std::string filename); // Loads materials from material libraries
        std::vector<Point3D> *verts; // Vertex coordinates
        std::vector<Point2D> *texVerts; // Texture vertices
        std::vector<Vec3D> *norms; // Normals
        std::map<std::string, Material> *mats; // Maps material names to integers
        std::vector<Face3D> *faces; // Mesh faces
	
    	/* Methods */
    	int convToLongInt(const char* str, long int* out);
    	int convToFloat(const char* str, float* out);
};

#endif // VERTEX3D_H
