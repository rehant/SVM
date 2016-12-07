#ifndef FACE3D_H
#define FACE3D_H

#include <vector>
#include <string>
#include "Vec3D.hpp"

class Face3D
{
	private:
		int v1, v2, v3, t1, t2, t3, n1, n2, n3;
		std::string mat_id;


	public:
		/**
		* Constructs a Face3D using parsed index data from a triangulated .obj file
		**/
		Face3D(int v1, int v2, int v3, int t1, int t2, int t3, int n1, int n2, int n3, std::string mat_id);

		// Vertex indices
		int getV1();
		int getV2();
		int getV3();

		// Texture indices
		int getT1();
		int getT2();
		int getT3();

		// Normal indices
		int getN1();
		int getN2();
		int getN3();

		// Return current material id of face
		std::string getMatID();		
};

#endif
