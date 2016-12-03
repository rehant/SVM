#ifndef __MESH_HPP__
#define __MESH_HPP__

/* C++ STL */
#include <string>
#include <vector>

// My includes
#include "Colour.hpp"
#include "Vec3D.hpp"
#include "Face3D.hpp"
#include "Vertex2D.hpp"
#include "Material.hpp"

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

    private:
	void loadMats(std::string filename); // Loads materials from material libraries

        std::vector<Face3D> *faces; // Mesh faces
	std::vector<Vertex2D> *texVerts; // Texture vertices
	std::vector<Vec3D> *norms; // Normals
	std::vector<Material> *mats; // Materials
	
	/* Methods */
	int convToLongInt(const char* str, long int* out);
	int convToFloat(const char* str, float* out);
};

#endif // VERTEX3D_H
