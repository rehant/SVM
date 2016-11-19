#ifndef __MESH_HPP__
#define __MESH_HPP__

/* C++ STL */
#include <string>
#include <vector>
using namespace std;

// My includes
#include "Colour.hpp"
#include "Vertex3D.h"
#include "Face3D.h"
#include "Vertex2D.h"
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

        /**
        * Draws the mesh.
        */
        //void draw();

	vector<Vertex3D>* getVertices()
	{
		return verts;
	}

	vector<Face3D>* getFaces()
	{
		return faces;
	}

	vector<Vertex2D>* getTexVerts()
	{
		return texVerts;
	}

	vector<Vec3D>* getNorms()
	{
		return norms;
	}	

    private:
        vector<Vertex3D> *verts; // Mesh vertices
        vector<Face3D> *faces; // Mesh faces
	vector<Vertex2D> *texVerts; // Texture vertices
	vector<Vec3D> *norms; // Normals
};

#endif // VERTEX3D_H
