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
#include <utility> // pair
using namespace std;

/* C includes */
#include <cstdlib> // strtof
#include <cmath> // HUGE_VAL
#include <cerrno> // errno

Mesh::Mesh(string filename)
{
	/* Internal vars */
	ifstream meshStream(filename.c_str()); // Stream for reading from file
	string line; // Line from file
	stringstream* lsp; // Line splitter string stream
	string com; // Current command
	string dname(filename); // String which will hold directory name (initialized to filename)
	
	// Extract directory name
	dname.erase(find(dname.rbegin(), dname.rend(), '/').base(), dname.end()); // Get directory name
	//cout << "Mesh directory name = " << dname << endl;

	stringstream matFNameGen; // Stringstream used to create the material file name

	/* Create class vectors */
	//cout << "Mesh::Mesh: creating vectors" << endl;
	verts = new vector<Point3D>(); // Internal vector. Vertices in here are added to faces
	texVerts = new vector<Point2D>();
	norms = new vector<Vec3D>();
	mats = new map<string, Material>(); // Create material index map
	faces = new vector<Face3D>(); // Create vector of faces

	string curMaterial; // Current material name for a set of faces in the file

	if (meshStream.is_open())
	{
		//cout << "Opened mesh file \"" << filename << "\"" << endl;

		while (getline(meshStream, line)) // Read from file
		{
			//cout << "Current line:" << line << endl;
			lsp = new stringstream(line); // Put the current line into the stringstream
			//std::cout << "lsp = \"" << lsp->str() << "\"" << endl;
			*lsp >> com; // Read the command
			//cout << "\tCommand = \"" << com << "\"" << endl;

			/* Handle commands */
			if (com == "v") // Vertex
			{
				float x, y, z;

				/*cout << "\tVertex" << endl;
				cout << "\tDetected vertex coordinates" << endl;
			
				/* X */
				*lsp >> com; // Read x
				convToFloat(com.c_str(), &x);	
				//cout << "\t\tx = " << x << endl;
	
				/* Y */
				*lsp >> com; // Read y
				convToFloat(com.c_str(), &y);	
				//cout << "\t\ty = " << y << endl;

				/* Z */
				*lsp >> com; // Read z
				convToFloat(com.c_str(), &z);	
				//cout << "\t\tz = " << z << endl;

				verts->push_back(Point3D(x, y, z)); // Create and add vertex to list
			}

			else if (com == "vt") // Texture vertex
			{
				//cout << "\tDetected texture vertex" << endl;

				float u, v; // U and V coords for vertices
				
				/* Read U */
				*lsp >> com;
				convToFloat(com.c_str(), &u);
				//cout << "\t\tu = " << u << endl;

				/* Read V */
				*lsp >> com;
				convToFloat(com.c_str(), &v);
				//cout << "\t\tv = " << v << endl;

				texVerts->push_back(Point2D(u, v)); // Add texture vertex
			}

			else if (com == "vn") // Normal
			{
				/*cout << "\tDetected normal" << endl;
				cout << "\tDetected normal vector" << endl;*/

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

				/*cout << "\tRead normal (" << x << ", " << y << ", " << z << ")" << endl;	
				cout << "\t\tRead normal (" << x << ", " << y << ", " << z << ")" << endl;	*/
				norms->push_back(Vec3D(x, y, z));
			}

			else if (com == "mtllib") // Material library
			{
				cout << "\tDetected material library" << endl;
				*lsp >> com; // Read file name
				cout << "Material file name: " << com << endl;
				matFNameGen << dname << com; // Create path to materials file (taking directory into account)
				loadMats(matFNameGen.str()); // Load materials from material files
			}

			else if (com == "usemtl") // Sets current material id
			{
				cout << "\tDetected current material" << endl;
				*lsp >> com; // Read name of current material
				curMaterial = com; // Save current material of faces to use to create face objects
				cout << "\t\tCurrent material = " << curMaterial << endl;
			}


			else if (com == "f") // Faces; parses face lines and makes face objects via indices
			{
				cout << "\tDetected face" << endl;

			//	float v1, v2, v3, t1, t2, t3, n1, n2, n3;
				float v1, v2, v3, t1, t2, t3, n1, n2, n3;
				
				/* Read v1 */
				getline(*lsp, com, '/');
				cout << "v1 str = \"" << com << "\"" << endl;
				convToFloat(com.c_str(), &v1);

				/* Read t1 */
				getline(*lsp, com, '/');
				cout << "t1 str = \"" << com << "\"" << endl;
				convToFloat(com.c_str(), &t1);

				/* Read n1 */
				/* KILL THE NASTY LITTLE SPACE */
				getline(*lsp, com, ' ');
				cout << "n1 str = \"" << com << "\"" << endl;
				convToFloat(com.c_str(), &n1);

				/* Read v2 */
				getline(*lsp, com, '/');
				cout << "v2 str = \"" << com << "\"" << endl;
				convToFloat(com.c_str(), &v2);

				/* Read t2 */
				getline(*lsp, com, '/');
				cout << "t2 str = \"" << com << "\"" << endl;
				convToFloat(com.c_str(), &t2);

				/* Read n2 */
				/* KILL THE NASTY LITTLE SPACE */
				getline(*lsp, com, ' ');
				cout << "n2 str = \"" << com << "\"" << endl;
				convToFloat(com.c_str(), &n2);

				/* Read v3 */
				getline(*lsp, com, '/');
				cout << "v3 str = \"" << com << "\"" << endl;
				convToFloat(com.c_str(), &v3);

				/* Read t3 */
				getline(*lsp, com, '/');
				cout << "t3 str = \"" << com << "\"" << endl;
				convToFloat(com.c_str(), &t3);

				/* Read n3 */
				/* KILL THE NASTY LITTLE SPACE */
				getline(*lsp, com, ' ');
				cout << "n3 str = \"" << com << "\"" << endl;
				convToFloat(com.c_str(), &n3);

				// Save face index parameters in a face object to vector of faces
				faces->push_back(Face3D(v1, v2, v3, t1, t2, t3, n1, n2, n3, curMaterial));

				cout << "\t\tReadface (" << v1 << ", " << v2 << ", " << v3 << ", " << t1 << ", " << t2 << ", " << t3 << ", " << n1 << ", " << n2 << ", " << n3 << ", " << curMaterial << ")" << endl;
			}

			delete lsp;
		}

		meshStream.close();
		calcBBox(); // Find this mesh's bounding box
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
	delete bbox; // Delete bounding box
	delete faces; // Delete vector of faces
	delete mats; // Delete map of names to indices
	delete norms; // Delete normals vector
	delete texVerts; // Delete texture vertices vector
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
	stringstream *lsp; // Line splitter
	string typ; // Type of data on a given line
	float ar, ag, ab; // Red, green. and blue values for ambient colour
	float dr, dg, db; // Red, green and blue for diffuse colour
	string matName; // Name of the current material
	float shiny; // Shinyness
	float sr, sg, sb; // Specular RGB
	bool matInProgress = false; // Whether or not we are currently reading the values for a material

	if (f.is_open()) // File opened
	{
		while (getline(f, line))
		{
			lsp = new stringstream(line); // Replace stringstream contents with line
			cout << lsp->str() << endl; // Debuggin- print stringstream contents to ensure they're correct
			*lsp >> typ; // Read type of data

			if (typ == "newmtl") // Start of new material
			{
				*lsp >> typ; // Read material name

				if (matInProgress) // We were already reading a material
				{
					cout << "Material in progress, saving it, starting new one" << endl;
					Colour amb(255*ar, 255*ag, 255*ab); // Ambient colour
					Colour diff(255*dr, 255*dg, 255*db); // Diffuse colour
					Colour spec(255*sr, 255*sg, 255*sb); // Specular colour
					matName = typ;
					pair<string, Material> toInsert = make_pair(matName, Material(amb, diff, spec, 128*shiny, matName)); // Shiny values are on 0-1 scale in file, but on 0-128 scale in OpenGL
					mats->insert(toInsert);
					matInProgress = false; // So that we'll start a new material next time
				}

				else
				{
					cout << "New material" << endl;
					matInProgress = true; // Mark this as in progress
					matName = typ; // Save material name
				}
			}

			else if (typ == "Kd") // Diffuse colour
			{
				/** Read info **/

				/* Red */
				*lsp >> typ; // Read red
				convToFloat(typ.c_str(), &dr); // Convert it

				/* Green */
				*lsp >> typ; // Read value
				convToFloat(typ.c_str(), &dg); // Convert it
		
				/* Blue */
				*lsp >> typ; // Read value
				convToFloat(typ.c_str(), &db); // Convert it

				cout << "Diffuse colour = (" << 255*dr << ", " << 255*dg << ", " << 255*db << ")" << endl;
			}

			else if (typ == "Ka") // Ambient colour
			{
				/** Read info **/

				/* Red */
				*lsp >> typ; // Read red
				convToFloat(typ.c_str(), &ar); // Convert it

				/* Green */
				*lsp >> typ; // Read value
				convToFloat(typ.c_str(), &ag); // Convert it
		
				/* Blue */
				*lsp >> typ; // Read value
				convToFloat(typ.c_str(), &ab); // Convert it

				cout << "Ambient colour = (" << 255*ar << ", " << 255*ag << ", " << 255*ab << ")" << endl;
			}

			else if (typ == "Tf") // Specular
			{
				/** Read info **/

				/* Red */
				*lsp >> typ; // Read red
				convToFloat(typ.c_str(), &sr); // Convert it

				/* Green */
				*lsp >> typ; // Resd vslue
				convToFloat(typ.c_str(), &sg); // Convert it
		
				/* Blue */
				*lsp >> typ; // Resd vslue
				convToFloat(typ.c_str(), &sb); // Convert it

				cout << "Specular colour = (" << 255*sr << ", " << 255*sg << ", " << 255*sb << ")" << endl;
			}

			else if (typ == "Ni") // Shininess
			{
				*lsp >> typ; // Read shininess
				convToFloat(typ.c_str(), &shiny); // Convert it
				cout << "Shininess = " << shiny << endl;
			}

			else
			{
				cout << "typ = " << typ << endl;
			}

			delete lsp;
		}
		
		if (matInProgress) // We were reading a material when the file ended
		{
			cout << "Material \"" << matName << "\" in progress at file end, creating it and adding it to map" << endl;
			Colour amb(255*ar, 255*ag, 255*ab); // Ambient colour
			Colour diff(255*dr, 255*dg, 255*db); // Diffuse colour
			Colour spec(255*sr, 255*sg, 255*sb); // Specular colour
			pair<string, Material> toInsert = make_pair(matName, Material(amb, diff, spec, 128*shiny, matName)); // Shiny values are on 0-1 scale in file, but on 0-128 scale in OpenGL
			cout << "pair = (" << toInsert.first << ", " << toInsert.second.getName() << ")" << endl;
			mats->insert(toInsert);
			cout << "Name of material in map = " << mats->at(matName).getName() << endl;
			//*mats[matName] = Material(amb, diff, spec, 128*shiny, matName);
		}

		f.close();
	}

	else
	{
//		cerr << "Unable to open file " << filename << endl;
	}
}

// Copy constructor
Mesh::Mesh(Mesh& other)
{
	/* Copy data */
	verts = new vector<Point3D>(other.getVerts());
	texVerts = new vector<Point2D>(other.getTexVerts());
	norms = new vector<Vec3D>(other.getNorms());
	faces = new vector<Face3D>(other.getFaces());
	mats = new map<string, Material>(other.getMats());
}

vector<Point3D> Mesh::getVerts()
{
	return *verts;
}

vector<Point2D> Mesh::getTexVerts()
{
	return *texVerts;
}

vector<Vec3D> Mesh::getNorms()
{
	return *norms;
}

map<string, Material> Mesh::getMats()
{
	return *mats;
}

vector<Face3D> Mesh::getFaces()
{
	return *faces;
}

/*void Mesh::operator=(const Mesh& other)
{
	/* Delete old vectors */
/*	delete norms;
	delete texVerts;
	delete verts;
	
	/* Copy data */
/*	this->verts = new vector<Vertex3D>(other.getVerts());
	this->texVerts = new vector<Point2D>(other.getTexVerts());
	this->norms = new vector<Vertex3D>(other.getNorms());
	this->faces = new vector<Face3D>(other.getFaces());
}*/

Material Mesh::getMaterial(string name)
{
	clog << (mats->find(name) != mats->end()) << endl;
	return mats->at(name);
}

void Mesh::calcBBox() // Calculates the bounding box of the mesh
{
	float lbbx, lbby, lbbz; // Left bottom back
	float rtfx, rtfy, rtfz; // RIght top front

	/* Search list of points */
	for (int i = 0; i < verts->size(); i++)
	{
		Point3D pt = verts->at(i);
		float curX = pt.getX();
		float curY = pt.getY();
		float curZ = pt.getZ();

		if (curX < lbbx) // FUrther left
		{
			lbbx = curX;
		}

		if (curX > rtfx) // Further right
		{
			rtfx = curX;
		}

		if (curY < lbby) // Further down
		{
			lbby = curY;
		}

		if (curY > rtfy) // Futher up
		{
			rtfy = curY;
		}

		if (curZ < lbbz) // Further back
		{
			lbbz = curZ;
		}

		if (curZ > rtfz) // Further front
		{
			rtfz = curZ;
		}
	}

	Point3D botBackLeft(lbbx, lbby, lbbz); // Bottom back left point
	Point3D topFrontRight(rtfx, rtfy, rtfz); // Top front right point
	bbox = new BoundingBox(botBackLeft, topFrontRight);
}
