#include "Mesh.hpp" // Class definition

// C++ includes
#include <fstream> // ifstream
#include <sstream> // stringstream
#include <string> // string
#include <iostream> // cout
#include <vector> // vector
#include <ios> // failure
#include <stdexcept> // length_error
#include <algorithm> // find
using namespace std;

/* C includes */
#include <cstdlib> // strtof
#include <cmath> // HUGE_VAL
#include <cerrno> // errno

Mesh::Mesh(string filename)
{
	/* Internal vars */
	vector<Vec3D> verts; // Internal vector. Vertices in here are added to faces
	ifstream meshStream(filename.c_str()); // Stream for reading from file
	string line; // Line from file
	stringstream* lsp; // Line splitter string stream
	string com; // Current command
	string dname(filename); // String which will hold directory name (initialized to filename)
	
	// Extract directory name
	dname.erase(find(dname.rbegin(), dname.rend(), '/').base(), dname.end()); // Get directory name
	cout << "Mesh directory name = " << dname << endl;

	stringstream matFNameGen; // Stringstream used to create the material file name

	/* Create class vectors */
	cout << "Mesh::Mesh: creating vectors" << endl;
	faces = new vector<Face3D>();
	texVerts = new vector<Vertex2D>();
	norms = new vector<Vec3D>();
	mats = new vector<Material>();

	if (meshStream.is_open())
	{
		cout << "Opened mesh file \"" << filename << "\"" << endl;

		while (getline(meshStream, line)) // Read from file
		{
			cout << "Current line:" << line << endl;
			lsp = new stringstream(line); // Put the current line into the stringstream
			std::cout << "lsp = \"" << lsp->str() << "\"" << endl;
			*lsp >> com; // Read the command
			cout << "\tCommand = \"" << com << "\"" << endl;

			/* Handle commands */
			if (com == "v") // Vertex
			{
				float x, y, z;

				cout << "\tVertex" << endl;
			
				/* X */
				*lsp >> com; // Read x
				convToFloat(com.c_str(), &x);	
				cout << "\t\tx = " << x << endl;
	
				/* Y */
				*lsp >> com; // Read y
				convToFloat(com.c_str(), &y);	
				cout << "\t\ty = " << y << endl;

				/* Z */
				*lsp >> com; // Read z
				convToFloat(com.c_str(), &z);	
				cout << "\t\tz = " << z << endl;

				verts.push_back(Vec3D(x, y, z)); // Create and add vertex to list
			}

			else if (com == "f") // Face
			{
				cout << "\tDetected face" << endl;
			}

			else if (com == "vt") // Texture vertex
			{
				cout << "\tDetected texture vertex" << endl;

				float u, v; // U and V coords for vertices
				
				/* Read U */
				*lsp >> com;
				convToFloat(com.c_str(), &u);
				cout << "\t\tu = " << u << endl;

				/* Read V */
				*lsp >> com;
				convToFloat(com.c_str(), &v);
				cout << "\t\tv = " << v << endl;

				texVerts->push_back(Vertex2D(u, v)); // Add texture vertex
			}

			else if (com == "vn") // Normal
			{
				cout << "\tDetected normal" << endl;

				float x, y, z;
			
				/* Read X */
				*lsp >> com;
				convToFloat(com.c_str(), &x);
			
				/* Read Y */
				*lsp >> com;
				convToFloat(com.c_str(), &y);
				
				/* Read Z */
				*lsp >> com;
				convToFloat(com.c_str(), &z);

				cout << "\tRead normal (" << x << ", " << y << ", " << z << ")" << endl;	
				norms->push_back(Vec3D(x, y, z));
			}

			else if (com == "mtllib") // Material library
			{
				*lsp >> com; // Read file name
				cout << "Material file name: " << com << endl;
				matFNameGen << dname << com; // Create path to materials file (taking directory into account)
				loadMats(matFNameGen.str()); // Load materials from material files
			}

			delete lsp;
		}

		meshStream.close();
	}

	else
	{
		cout << "Failed to open mesh file \"" << filename << "\"" << endl;
	}
}

/**
* Destructor. Performs cleanup when mesh is deleted.
*/
Mesh::~Mesh()
{
	cout << "Mesh::~Mesh: deleting vectors" << endl;
	delete mats;
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

/* Load materials from material file */
void Mesh::loadMats(string filename)
{
	ifstream f(filename.c_str()); // Create an object to read from the file
	string line; // Holds a line
	stringstream lsp; // Line splitter
	string typ; // Type of data on a given line
	float r, g, b; // Red, green. and blue values for the colours
	bool matStarted = false; // Whether or not a material has been started
	string matName; // Name of the current material

	if (f.is_open()) // File opened
	{
		while (getline(f, line))
		{
			lsp.str(line); // Replace stringstream contents with line
			cout << lsp.str() << endl; // Debuggin- print stringstream contents to ensure they're correct
			lsp >> typ; // Read the string type

			if (typ == "Kd") // Diffuse colour
			{
				/* Red comp */
				lsp >> typ; // Read red comp val
				convToFloat(typ.c_str(), &r); // Convert to number

				/* Green component */
				lsp >> typ;
				convToFloat(typ.c_str(), &g);

				/* Green component */
				lsp >> typ;
				convToFloat(typ.c_str(), &b);
	
				cout << "Diffuse colour is (" << r << ", " << g << ", " << b << ")" << endl;
			}

			else if (typ == "newmtl") // New material name
			{
				lsp >> matName; // Read material name
				matStarted = true;
			}
		}

		f.close();
	}

	else
	{
		cerr << "Unable to open file " << filename << endl;
	}
}
