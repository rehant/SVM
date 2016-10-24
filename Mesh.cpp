#include "Mesh.hpp" // Class definition

// C++ includes
#include <fstream> // ifstream
#include <sstream> // istringstream
#include <string> // string
#include <iostream> // cout
using namespace std;

/* C includes */
#include <cstdlib> // strtof
#include <cmath> // HUGE_VAL
#include <cerrno> // errno

Mesh::Mesh3D(string filename)
{
    ifstream objFile(filename.c_str()); // Create the file object
    char line[256]; // Line in file
    istringstream lineSplitter(); // Used to split lines by whitespace. Initialised with empty string.
    string curToken; // Current token in current line
    float vx, vy, vz; // X, Y, and Z for current vertex.
    int convVal; // Return value of converting function
    long int[] finds[4]; // Index used to read face indices

    /* Construct vectors */
    verts = new vector<Vertex3D>(); // Create Vertex3D vector
    faces = new vector<Face3D>(); // Create Face3D vector
    colours = new vector<Colour>(); // Create Colour vector

    try
    {
        if (objFile.is_open()) // File opened successfully
        {
            while (objFile.good()) // Keep reading lines from the stream until we reach the end of the file
            {
                objFile.getLine(line); // Get a line from the file
                lineSplitter.str(string(line)); // Copy the l
                curToken << lineSplitter; // Read the command token

                if (curToken == "v") // Vertex. Parameters: float x, float y, float z
                {
                    /* Read x */
                    curToken << lineSplitter; // Read string
                    convVal = convToFloat(curToken.c_str(), &vx); // Try to convert string

                    if (convVal != 0) // Error
                    {
                        cout << "Mesh: Error converting vx (" << curToken << ") to string" << endl;
                        exit(convVal); // Exit with error
                    }

                    /* Read y */
                    curToken << lineSplitter; // Read string
                    convVal = convToFloat(curToken.c_str(), &vy); // Try to convert string

                    if (convVal != 0) // Error
                    {
                        cout << "Mesh: Error converting vy (" << curToken << ") to string" << endl;
                        exit(convVal); // Exit with error
                    }

                    /* Read z */
                    curToken << lineSplitter; // Read string
                    convVal = convToFloat(curToken.c_str(), &vz); // Try to convert string

                    if (convVal != 0) // Error
                    {
                        cout << "Mesh: Error converting vz (" << curToken << ") to string" << endl;
                        exit(convVal); // Exit with error
                    }

                    verts->push_back(Vertex3D(vx, vy, vz)); // Add it to the vector of vertices
                }

                else if (curToken == "f") // Face: int[] vertInds; (an array of indices into the array of vertices)
                {
                    /* Read index 0 */
                    curToken << lineSplitter; // Read first index
                    convVal = convToLongInt(curToken.c_str(), &finds[0]); // Try to convert the string

                    if (convVal != 0) // Error
                    {
                        cout << "Mesh: error in converting f[0]" << endl;
                        exit(convVal);
                    }

                    /* Read index 1 */
                    curToken << lineSplitter; // Read first index
                    convVal = convToLongInt(curToken.c_str(), &finds[1]); // Try to convert the string

                    if (convVal != 0) // Error
                    {
                        cout << "Mesh: error in converting f[1]" << endl;
                        exit(convVal);
                    }

                    /* Read index 2 */
                    curToken << lineSplitter; // Read first index
                    convVal = convToLongInt(curToken.c_str(), &finds[2]); // Try to convert the string

                    if (convVal != 0) // Error
                    {
                        cout << "Mesh: error in converting f[2]" << endl;
                        exit(convVal);
                    }

                    /* Read index 3 */
                    curToken << lineSplitter; // Read first index
                    convVal = convToLongInt(curToken.c_str(), &finds[3]); // Try to convert the string

                    if (convVal != 0) // Error
                    {
                        cout << "Mesh: error in converting f[3]" << endl;
                        exit(convVal);
                    }

                    faces->push_back(Face3D(finds)); // Create new face using given indices
                }
            }

            objFile.close(); // Close the file
        }
    }

    catch ()
}

/**
* Destructor. Performs cleanup when mesh is deleted.
*/
Mesh3D::~Mesh3D()
{
    delete colours; // Delete vector of colours
    delete faces; // Delete vector of faces
    delete verts; // Delete vector of vertices
}

/**
* Converts a string to a floating-point number, returning a status.
* @param str The string to convert.
* @param out A pointer to an integer in which the result will be stored.
* @return   1 if the string contained characters other than digits, whitespace, or a period
            2 if no conversion was performed
            3 if overflow would occur
            4 if underflow would occur.
*/
int convToFloat(char* str, float* out)
{
    char endPtr[256]; // Stores end pointer of string
    *out = strtof(str, &endPtr); // Try to convert string

    if (endPtr[0] != '\0') // End pointer isn't null, string wasn't valid #
    {
        return 1;
    }

    if (*out == 0 && endptr == str) // No conversion performed
    {
        return 2;
    }

    if (errno == ERANGE) // Range error
    {
        if (*out == HUGE_VALF || *out == -HUGE_VALF) // Overflow
        {
            return 3;
        }

        if (*out == 0) //  Underflow
        {
            return 4;
        }
    }

    return 0; // All OK
}

/**
* Converts a string to a long int, returning a status.
* @param str The string to convert.
* @param out A pointer to a long integer in which the result will be stored.
* @return   1 if the string contained characters other than digits, whitespace, or a period
            2 if no conversion was performed
            3 if overflow would occur
            4 if underflow would occur.
*/
int convToLongInt(char* str, long int* out)
{
    char endPtr[256]; // Stores end pointer of string
    *out = strtol(str, &endPtr); // Try to convert string

    if (endPtr[0] != '\0') // End pointer isn't null, string wasn't valid #
    {
        return 1;
    }

    if (*out == 0 && endptr == str) // No conversion performed
    {
        return 2;
    }

    if (errno == ERANGE) // Range error
    {
        if (*out == HUGE_VALF || *out == -HUGE_VALF) // Overflow
        {
            return 3;
        }

        if (*out == 0) //  Underflow
        {
            return 4;
        }
    }

    return 0; // All OK
}
