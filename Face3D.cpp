#include "Face3D.hpp"
#include "Vertex3D.h"

/**
* Constructs a Face3D with the vertices in the given array.
**/
Face3D::Face3D(vector<Vertex3D> uVerts)
{
        verts = new vector<Vertex3D>(); // Create the vector.

        for (int i = 0; i < uVerts.size(); i++)
        {
            verts->push_back(uVerts[i]); // Add it to our vector
        }
}

/**
* Destructor. Destroys a face.
*/
Face3D::~Face3D()
{
        delete verts; // Delete the vector
}
