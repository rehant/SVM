#include "GeometryNode.hpp"

GeometryNode::GeometryNode(int geomType)
{
	geom = geomType; // Save geometry type
}

GeometryNode::~GeometryNode()
{
}

int GeometryNode::getGeom()
{
	return geom;
}
