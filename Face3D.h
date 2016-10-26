#ifndef FACE3D_H
#define FACE3D_H

#include <vector>
using namespace std;

struct Face3D
{
    vector<int> *verts; // List of vertices in the face

	/**
	* Constructs a Face3D with the vertices in the given array.
	**/
	Face3D(vector<int> uVerts)
	{
        verts = new vector<int>(); // Create the vector.

        for (int i = 0; i < uVerts.size(); i++)
        {
            verts->push_back(uVerts[i]); // Add it to our vector
        }
	}

	/**
	* Destructor. Destroys a face.
	*/
	~Face3D()
	{
        delete verts; // Delete the vector
	}
};
#endif
