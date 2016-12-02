#include "Face3D.hpp"
#include "Vertex3D.h"

/**
* Constructs a Face3D with the vertices in the given array.
**/
Face3D::Face3D(vector<Vertex3D> uVerts)
{
        verts = new vector<Vertex3D>(uVerts); // Copy the vector into ours
}

/**
* Destructor. Destroys a face.
*/
Face3D::~Face3D()
{
        delete verts; // Delete the vector
}
