#include "Mesh.hpp" // Class definition

// C++ includes
#include <fstream>

Mesh::Mesh3D(string filename)
{
    ifstream objFile(filename.c_str()); // Create the file object
    char line[256]; // Line in file

    try
    {
        if (objFile.is_open()) // File opened successfully
        {
            while (objFile.good()) // Keep reading lines from the stream until we reach the end of the file
            {
                objFile.getLine();
            }

            objFile.close(); // Close the file
        }
    }

    catch ()
}
