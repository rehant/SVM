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

class Mesh3D
{
    public:
        /**
        * Constructor. Loads a .OBJ file into an object.
        */
        Mesh3D(string filename);

        /**
        * Draws the mesh.
        */
        void draw();

    private:
        vector<vertex3D> *verts;
        vector<face3D> *faces;
        vector<Colour> *colours;
};

#endif // VERTEX3D_H
