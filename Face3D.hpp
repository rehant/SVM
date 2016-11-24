#ifndef FACE3D_H
#define FACE3D_H

#include <vector>
#include "Vertex3D.h"
using namespace std;

class Face3D
{

	public:
		/**
		* Constructs a Face3D with the vertices in the given array.
		**/
		Face3D(vector<Vertex3D> uVerts);
	
		/**
		* Destructor. Destroys a face.
		*/
		~Face3D();

		vector<Vertex3D>* getVerts()
		{
			return verts;
		}
	
	private:
    		vector<Vertex3D> *verts; // List of vertices in the face
};
#endif
