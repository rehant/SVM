#include "Mesh.hpp" // Class definition

// C++ includes
#include <fstream> // ifstream
#include <sstream> // stringstream
#include <string> // string
#include <iostream> // cout
#include <vector> // vector
#include <ios> // failure
#include <stdexcept> // length_error
#include <regex> // regex
using namespace std;

/* C includes */
#include <cstdlib> // strtof
#include <cmath> // HUGE_VAL
#include <cerrno> // errno

Mesh::Mesh(string filename)
{
    ifstream objFile(filename.c_str()); // Create the file object
    char line[256]; // Line in file
    stringstream lineSplitter(); // Used to split lines by whitespace. Initialised with empty string.
    string curToken = ""; // Current token in current line
    float vx, vy, vz = 0.0, 0.0, 0.0; // X, Y, and Z for current vertex.
    int convVal; // Return value of converting function
    vector<int> finds(); // Vector storing vertex indices for a face
    long int convInd;
    int numInds = 0; // Number of indices in 1 face
	regex fVInd("f ([\+|-])*([0-9]+)*"); // Regex for matching a face with only vertex indices
	regex fNormInd("f ([\+|-])*([0-9]+\/[0-9]+\/[0-9]+)*"); // Regex matching a line with verte tecture coord indices

    /* Construct vectors */
    verts = new vector<Vertex3D>(); // Create Vertex3D vector
    faces = new vector<Face3D>(); // Create Face3D vector
	texVerts = new vector<Vertex2D>(); // Create texture vertices vector
	norms = new vector<Vec3D>(); // Create normals vector

    try
    {
        if (objFile.is_open()) // File opened successfully
        {
            while (objFile.good()) // Keep reading lines from the stream until we reach the end of the file
            {
                objFile.getline(line); // Get a line from the file
                lineSplitter.str(string(line)); // Copy the l
                curToken << lineSplitter; // Read the command token

                if (curToken == "v") // Vertex. Parameters: float x, float y, float z
                {
                    /* Read x */
                    curToken << lineSplitter; // Read string
                    convVal = convToFloat(curToken.c_str(), &vx); // Try to convert string

                    if (convVal != 0) // Error
                    {
                        cout << "Mesh: Error converting vx (" << curToken << ") to float" << endl;
                        exit(convVal); // Exit with error
                    }

                    /* Read y */
                    curToken << lineSplitter; // Read string
                    convVal = convToFloat(curToken.c_str(), &vy); // Try to convert string

                    if (convVal != 0) // Error
                    {
                        cout << "Mesh: Error converting vy (" << curToken << ") to float" << endl;
                        exit(convVal); // Exit with error
                    }

                    /* Read z */
                    curToken << lineSplitter; // Read string
                    convVal = convToFloat(curToken.c_str(), &vz); // Try to convert string

                    if (convVal != 0) // Error
                    {
                        cout << "Mesh: Error converting vz (" << curToken << ") to float" << endl;
                        exit(convVal); // Exit with error
                    }

                    verts->push_back(Vertex3D(vx, vy, vz)); // Add it to the vector of vertices
                }

                else if (curToken == "f") // Face: int[] vertInds; (an array of indices into the array of vertices)
                {
			if (regex_match(lineSpitter, fvInd)) // Vertex indices for face
			{
	                    while (lineSplitter.good()) // While we can still read from the stream
	                    {
	                        curToken << lineSplitter; // Read the next index
	                        convVal = convToLongInt(curToken.c_str(), &convInd); // Convert the string to a long int
	
	                        if (convVal != 0) // Error
	                        {
	                            cout << "Mesh: Error converting convInd (" << curToken << ") to long int" << endl;
	                            exit(convVal); // Exit with error
	                        }
	
	                        finds->push_back(convInd); // Add it to the vector
	                    }
	
	                    faces->push_back(Face3D(finds)); // Create new face using given indices
			}

			else if (regex_match(
                }

                else if (curToken == "mtllib") // Material library file
                {
                    curToken << lineSplitter; // Read the path to the materials file
                }

		else if (curToken == "vt") // Texture vertex
		{
			/* Texture coords */
			float tx;
			float ty;

			curToken << lineSplitter; // Read coord one
			convToFloat(curToken.c_str(), &tx); // Convert to float
			curToken << lineSplitter; // Read coord two
			convToFloat(curToken.c_str(), &ty); // Convert coord 2
			texVerts->push_back(Vertex2D(tx, ty)); // Save texture vertex
		}

		else if (curToken == "vn") // Vertex normal
		{
			float nx, ny, nz;
			
			/* Read and convert coords */
			curToken << lineSplitter;
			convToFloat(curToken.c_str(), &nx);
			
			curToken << lineSplitter;
			convToFloat(curToken.c_str(), &ny);

			curToken << lineSplitter;
			convToFloat(curToken.c_str(), &nz);

			/* Create and add the normal */
			norms->push_back(Vec3D(nx, ny, nz)); // Add the normal
		}
            }

            objFile.close(); // Close the file
        }
    }

    catch (failure& f) // getline
    {
        cerr << "Caught failure exception: " << f.what() << endl;
        exit(-1);
    }

    catch (length_error& le)
    {
        cerr << "Caught length_error exception: " << le.what() << endl;
        exit(-2);
    }
}

/**
* Destructor. Performs cleanup when mesh is deleted.
*/
Mesh::~Mesh()
{
	delete norms; // Delete normals vector
	delete texVerts; // Delete texture vertices vector
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
