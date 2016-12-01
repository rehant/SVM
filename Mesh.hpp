#ifndef __MESH_HPP__
#define __MESH_HPP__

/* C++ STL */
#include <string>
#include <vector>
using namespace std;

// My includes
#include "Colour.hpp"
#include "Vec3D.hpp"
#include "Face3D.hpp"
#include "Vertex2D.hpp"
#include "Vec3D.hpp"

class Mesh
{
    public:
        /**
        * Constructor. Loads a .OBJ file into an object.
        */
        Mesh(string filename);

        /**
        * Destructor. Performs cleanup when mesh is deleted.
        */
        ~Mesh();

    private:
        vector<Face3D> *faces; // Mesh faces
	vector<Vertex2D> *texVerts; // Texture vertices
	vector<Vec3D> *norms; // Normals
	
	/* Methods */
	int convToLongInt(const char* str, long int* out);
	int convToFloat(const char* str, float* out);
};

#endif // VERTEX3D_H
