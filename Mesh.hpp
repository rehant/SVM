#ifndef __MESH_HPP__
#define __MESH_HPP__

#include <vector>
using namespace std;

// My includes
#include "Colour.hpp"
#include "Vertex3D.h"
#include "Face3D.h"

class Mesh3D
{
    public:
        Mesh3D(); // Constructor
        void drawMesh();
        void load(); // WHy not load in constructor
        void loadOBJ(char *filename);

    private:
        vector<vertex3D> *verts;
        vector<face3D> *faces;
        vector<Colour> *colours;
};

#endif // VERTEX3D_H
