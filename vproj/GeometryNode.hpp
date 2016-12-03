#ifndef GEOMETRYNODE_HPP
#define GEOMETRYNODE_HPP

#include "SceneNode.hpp"

const int TEAPOT = 1;
const int CUBE = 2;
const int SPHERE = 3;

class GeometryNode : public SceneNode
{
    public:
        /** Default constructor */
        GeometryNode(int geomType);

	~GeometryNode();

    int getType() {return type;} // Type of node (scene, transform, geom)

	int getGeom();

    protected:
        int type = 4;
	int geom; // Geom type

    private:
};

#endif // GEOMETRYNODE_HPP
