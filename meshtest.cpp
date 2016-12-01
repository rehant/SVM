/**
* This file is meant to test the Mesh class.
**/

/* Standard includes */
#include <iostream>

/* My includes */
#include "Mesh.hpp" // Mesh class

int main()
{
	Mesh cube("Assets/cube.obj"); // Try to load the file
	Mesh track("Assets/track.obj");
	return 0;
}
