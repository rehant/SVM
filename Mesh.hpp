#ifndef __MESH_HPP__
#define __MESH_HPP__

/* C++ STL */
#include <string>
#include <vector>
#include <map>

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
        std::vector<Vec3D> *verts; // Vertex coordinates
        std::vector<Vertex2D> *texVerts; // Texture vertices
        std::vector<Vec3D> *norms; // Normals
        std::map<std::string, Material> *mats; // Materials
        std::vector<Face3D> *faces; // Mesh faces
	
    	/* Methods */
    	int convToLongInt(const char* str, long int* out);
    	int convToFloat(const char* str, float* out);
};

#endif // VERTEX3D_H
