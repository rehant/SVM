#ifndef FACE3D_H
#define FACE3D_H

#include <vector>
#include "Vec3D.hpp"

class Face3D
{

	public:
		/**
		* Constructs a Face3D using parsed index data from a triangulated .obj file
		**/
		Face3D(int v1, int v2, int v3, int t1, int t2, int t3, int n1, int n2, int n3, std::string mat_id);
	
		/**
		* Destructor. Destroys a face.
		*/
		//~Face3D();

		int getV1();
		int getV1();
		int getV1();

		int getT1();
		int getT2();
		int getT3();

		int getN1();
		int getN2();
		int getN3();
	
	private:
    		
};

#endif
