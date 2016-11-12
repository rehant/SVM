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

class Mesh
{
    public:
        /**
        * Constructor. Loads a .OBJ file into an object.
        */
        Mesh3D(string filename);

        /**
        * Destructor. Performs cleanup when mesh is deleted.
        */
        ~Mesh3D();

        /**
        * Draws the mesh.
        */
        void draw();

    private:
        vector<Vertex3D> *verts;
        vector<Face3D> *faces;
        vector<Colour> *colours;
};

#endif // VERTEX3D_H
