#ifndef FACE3D_H
#define FACE3D_H
struct Face3D
{
    long int verts[4]; // List of vertices in the face

    /**
	* Constructs a Face3D with the given vertices.
	**/
	Face3D(long int v1, long int v2, long int v3, long int v4)
	{
        /* Save vertices. */
        verts[0] = v1;
        verts[1] = v2;
        verts[2] = v3;
        verts[3] = v4;
	}

	/**
	* Constructs a Face3D with the vertices in the given array.
	**/
	Face3D(long int[] uVerts)
	{
        /* Save vertices. */
        verts[0] = uVerts[0];
        verts[1] = uVerts[1];
        verts[2] = uVerts[2];
        verts[3] = uVerts[3];
	}
};
#endif
