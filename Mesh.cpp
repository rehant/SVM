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
	/* Internal vars */
	vector<Vertex3D> verts; // Internal vector. Vertices in here are added to faces
	ifstream meshStream(filename); // Stream for reading from file
	string line; // Line from file
	stringstream* lsp; // Line splitter string stream
	string com; // Current command
	regex slashParam("[0-9]+/[0-9]+/[0-9]+"); // Regex matching a face entry with vt/vn/etc. entries
	regex hasSlashes("/"); // Regex to check if line has slashes

	/* Create class vectors */
	clog << "Mesh::Mesh: creating vectors" << endl;
	faces = new vector<Face3D>();
	texVerts = new vector<Vertex2D>();
	norms = new vector<Vec3D>();


	if (meshStream.is_open())
	{
		clog << "Opened mesh file \"" << filename << "\"" << endl;

		while (getline(meshStream, line)) // Read from file
		{
			clog << "Current line:" << line << endl;
			lsp = new stringstream(line); // Put the current line into the stringstream
			std::clog << "lsp = \"" << lsp->str() << "\"" << endl;
			*lsp >> com; // Read the command
			clog << "\tCommand = \"" << com << "\"" << endl;

			/* Handle commands */
			if (com == "v") // Vertex
			{
				float x, y, z;

				clog << "\tVertex" << endl;
			
				/* X */
				*lsp >> com; // Read x
				convToFloat(com.c_str(), &x);	
				clog << "\t\tx = " << x << endl;
	
				/* Y */
				*lsp >> com; // Read y
				convToFloat(com.c_str(), &y);	
				clog << "\t\ty = " << y << endl;

				/* Z */
				*lsp >> com; // Read z
				convToFloat(com.c_str(), &z);	
				clog << "\t\tz = " << z << endl;

				verts.push_back(Vertex3D(x, y, z)); // Create and add vertex to list
			}

			else if (com == "f") // Face
			{
				clog << "\tDetected face" << endl;
			 
				/* Check if face has info other than indices */
				if (regex_match(line, hasSlashes)) // Line has slashes
				{
					clog << "\tLine has slashes" << endl;
				}

				else // Line doesn't have slashes
				{
					clog << "\tLine doesn't have slashes" << endl;
				}
			}

			delete lsp;
		}

		meshStream.close();
	}

	else
	{
		clog << "Failed to open mesh file \"" << filename << "\"" << endl;
	}
}

/**
* Destructor. Performs cleanup when mesh is deleted.
*/
Mesh::~Mesh()
{
	clog << "Mesh::~Mesh: deleting vectors" << endl;
	delete norms; // Delete normals vector
	delete texVerts; // Delete texture vertices vector
    delete faces; // Delete vector of faces
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
int Mesh::convToFloat(const char* str, float* out)
{
    char* endPtr; // Stores end pointer of string
    *out = strtof(str, &endPtr); // Try to convert string

    if (endPtr[0] != '\0') // End pointer isn't null, string wasn't valid #
    {
        return 1;
    }

    if (*out == 0 && endPtr == str) // No conversion performed
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
int Mesh::convToLongInt(const char* str, long int* out)
{
    char* endPtr; // Stores end pointer of string
    *out = strtol(str, &endPtr, 10); // Try to convert string

    if (endPtr[0] != '\0') // End pointer isn't null, string wasn't valid #
    {
        return 1;
    }

    if (*out == 0 && endPtr == str) // No conversion performed
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
