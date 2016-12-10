// Main file for the project

// INCLUDING LOCAL FILES
#include "Mesh.hpp"
#include "Material.hpp"
#include "Point3D.hpp"
#include "Face3D.hpp"
#include "Vec3D.hpp"
#include "Point2D.hpp"
#include "obstacle.h"
#include "powerup.h"

// INCLUDING SYSTEM LIBRARIES
#include <stdio.h>
#include <stdlib.h> // atexit
#include <iostream>
#include <fstream> // ifstream
#include <vector>
#include <math.h>

// INCLUDING OPENGL LIBRARIES
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

using namespace std;

/*================================================
				GLOBALS VARIABLES
================================================*/
int winPos[2] = {50, 50};
int winSize[2] = {800, 600};

float camPos[] 	= {0, 40, 10};		// Position of camera
float tarPos[] = {0, 0, 0};			//where that camera is pointed at
float camUp[] = {0, 1, 0};

float lightPos0[] = {2, 10, 2, 1};	// Position of light0
float lightPos1[] = {100, 200, -60, 1};	// Position of light1

// Light paramter arrays (RGBA)
float amb_l[]	= {1, 1, 1, 1};
float diff_l[]	= {1, 1, 1, 1};
float spec_l[]	= {1, 1, 1, 1};

/* Track */
float trackPos[] = {0, 0, 0};
int angle = 0;
float xangle = 0;

// Init track pointer
Mesh* track = NULL;
Mesh* ship = NULL;

// Class Object Instances 
obstacle obstacle1 = obstacle(70, 4);
obstacle obstacle2 = obstacle(70, -4);
obstacle obstacle3 = obstacle(102, 70);
obstacle obstacle4 = obstacle(106, 70);
obstacle obstacle5 = obstacle(50, 90);
obstacle obstacle6 = obstacle(50, 94);
obstacle obstacle7 = obstacle(-29.5, 30);
obstacle obstacle8 = obstacle(-33.5, 30);
obstacle obstacle9 = obstacle(-37.5, 30);

powerup powerup1 = powerup(70, 0);
powerup powerup2 = powerup(110, 70);
powerup powerup3 = powerup(50, 86);


/*================================================
				DRAW METHODS
================================================*/

// Sets the created lights
void setLights(void)
{
	// LIGHT0 PARAMETERS
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb_l);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff_l);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec_l);
	
	// LIGHT1 PARAMETERS
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, amb_l);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diff_l);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spec_l);
}

// Draws the object
void drawMesh(Mesh *m)
{
	vector<Face3D> mfaces = m->getFaces(); // Get a list of the mesh's faces
	vector<Point3D> mverts = m->getVerts(); // Fetch vertices
	vector<Point2D> mtverts = m->getTexVerts(); // Fetch texture vertices
	vector<Vec3D> mnorms = m->getNorms(); // Normals
	Material *faceMaterial = NULL; // Stores the face's material
	string curMatName = ""; // Stores the name of the current material (to avoid fetching materials which we're already using)
	Point3D curVert;
	Vec3D curNorm;
	Point2D curTexVert;
	
	//cout << "Fetched mesh data" << endl;

	glBegin(GL_TRIANGLES); // Start drawing triangles

	for (int f = 0; f < mfaces.size(); f++)
	{
		//cout << "Face #" << f+1 << endl;

		int vinds[3]; // Array of vertex indices
		int ninds[3]; // Array of normal indices
		int tinds[3]; // Array of texture indices
		Face3D curFace = mfaces.at(f); // Fetch the current face
		
		//cout << "\tFetched face" << endl;

		if (curFace.getMatID() != curMatName) // Face uses a different material
		{
			if (faceMaterial != NULL) // Material was previously allocated
			{
				delete faceMaterial;
				faceMaterial = NULL;
			}

			curMatName = curFace.getMatID(); // Fetch the material ID so that the comparison will fail the next time (and so that we can fetch the material object)
			//cout << "\tcurMatName = \"" << curMatName << "\"" << endl;
			faceMaterial = new Material(m->getMaterial(curMatName));
			//cout << "\tFetched material " << curMatName << endl;
		
			
			// Fetch mesh colours 
			GLfloat m_amb[] = {faceMaterial->getAmb().getR(), faceMaterial->getAmb().getG(), faceMaterial->getAmb().getB(), 1.0};
			GLfloat m_dif[] = {faceMaterial->getDif().getR(), faceMaterial->getDif().getG(), faceMaterial->getDif().getB(), 1.0};
			GLfloat m_spec[] = {faceMaterial->getSpec().getR(), faceMaterial->getSpec().getG(), faceMaterial->getSpec().getB(), 1.0};
			GLint shininess = faceMaterial->getShine();
			
			// Upload data to GPU 
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
			glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
			
		}
		
		else
		{
			//cout << "\tNo need to fetch, material name = \"" << curMatName << "\"" << endl;
		}
			
		vinds[0] = curFace.getV1();
		vinds[1] = curFace.getV2();
		vinds[2] = curFace.getV3();

		ninds[0] = curFace.getN1();
		ninds[1] = curFace.getN2();
		ninds[2] = curFace.getN3();
	
		tinds[0] = curFace.getT1();
		tinds[1] = curFace.getT2();
		tinds[2] = curFace.getT3();

		//cout << "\tVertex indices = " << vinds[0] << ", " << vinds[1] << ", " << vinds[2] << endl;
		//cout << "\tNormal indices = " << ninds[0] << ", " << ninds[1] << ", " << ninds[2] << endl;
		//cout << "\tTexture indices = " << tinds[0] << ", " << tinds[1] << ", " << tinds[2] << endl;

		// Draw vertex 1 

		// Fetch data (subtract 1 because material indices start at 1) 
		curVert = mverts.at(vinds[0]-1);
		curNorm = mnorms.at(ninds[0]-1);
		curTexVert = mtverts.at(tinds[0]-1);

		// Draw it 
		glNormal3f(curNorm.getX(), curNorm.getY(), curNorm.getZ());
		glVertex3f(curVert.getX(), curVert.getY(), curVert.getZ());

		// Draw vertex 2

		// Fetch data 
		curVert = mverts.at(vinds[1]-1);
		curNorm = mnorms.at(ninds[1]-1);
		curTexVert = mtverts.at(tinds[1]-1);

		// Draw it 
		glNormal3f(curNorm.getX(), curNorm.getY(), curNorm.getZ());
		glVertex3f(curVert.getX(), curVert.getY(), curVert.getZ());

		// Draw vertex 3 

		// Fetch data 
		curVert = mverts.at(vinds[2]-1);
		curNorm = mnorms.at(ninds[2]-1);
		curTexVert = mtverts.at(tinds[2]-1);

		// Draw it 
		glNormal3f(curNorm.getX(), curNorm.getY(), curNorm.getZ());
		glVertex3f(curVert.getX(), curVert.getY(), curVert.getZ());

		}

	glEnd(); // End triangles
}

// Deletes objects on exit
void cleanup()
{
	if (track != NULL)
	{
		delete track;
		track = NULL;
	}
}

/*================================================
			OPENGL & GLUT DEFINED METHODS
================================================*/

void keyboard(unsigned char key, int xIn, int yIn)
{
	float alpha = 0.5; // Number of radians to rotate by

	switch(key)
	{
		case 27:
			exit(0);
			break;

		case 'd':
		case 'D':
		{
			angle++;
			break;
		}

		case 'a':
		case 'A':
		{
			angle--;
			break;
		}

		case 'w':
		case 'W':
		{
			trackPos[0]++;
			break;
		}

		case 's':
		case 'S':
		{
			trackPos[0]--;
			break;
		}
	}

	glutPostRedisplay();
}


// Implements a basic camera for now
void special(int key, int x, int y)
{
	switch (key)
	{
		// Move camera in positive z direction
		case GLUT_KEY_UP:
			camPos[2] += 2;
			break;

		// Move camera in negative z direction
		case GLUT_KEY_DOWN:
			camPos[2] -= 2;
			break;

		// Move camera in negative x direction
		case GLUT_KEY_LEFT:
			camPos[0] -= 2;
			break;

		// Move camera in positive x direction
		case GLUT_KEY_RIGHT:
			camPos[0] += 2;
			break;

		// Move camera in negative y direction
		case GLUT_KEY_PAGE_DOWN:
			camPos[1] -= 1;
			break;

		// Move camera in positive y direction
		case GLUT_KEY_PAGE_UP:
			camPos[1] += 1;
			break;
	}

	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{

}

void display(void)
{
	// Clears screen color buffer, and depth buffer on each callback
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set current matrix to Modelview
	glMatrixMode(GL_MODELVIEW);

	// Reset current modelview matrix stack
	glLoadIdentity(); // Load an identity

	// Set where we're looking at
	gluLookAt(camPos[0], camPos[1], camPos[2], tarPos[0], tarPos[1], tarPos[2], camUp[0], camUp[1], camUp[2]);

	// Sets how polygons are drawn
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glPushMatrix();

	/* Rotate track */
	glTranslatef(tarPos[0], tarPos[1], tarPos[2]);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glTranslatef(-tarPos[0], -tarPos[1], -tarPos[2]);

	// Draws track
	drawMesh(track);
	powerup1.draw();
	powerup2.draw();
	powerup3.draw();
	
	obstacle1.draw();
	obstacle2.draw();
	obstacle3.draw();
	obstacle4.draw();
	obstacle5.draw();
	obstacle6.draw();
	obstacle7.draw();
	obstacle8.draw();
	obstacle9.draw();
	glPopMatrix();

	// Swap into back buffer on each call to display 
	glutSwapBuffers();

	// Redisplay the screen
	//glutPostRedisplay();
}

void callBacks(void)
{
	// Runs display callback function
	glutDisplayFunc(display);

	// Runs keyboard callback function. Allows for keyboard input
	glutKeyboardFunc(keyboard);

	// Runs special callback function. Allows for special keyboard inputs
	glutSpecialFunc(special);

	// Runs mouse callback function. Allows for mouse inputs
	glutMouseFunc(mouse);

	// Cleans up memory
	atexit(cleanup);
}

void instructions()
{
	std::ifstream readmeStream("README", std::ifstream::in); // Open README file
	char c;

	if (readmeStream.is_open()) // Stream opened
	{
		while (readmeStream.good())
		{
			c = readmeStream.get();
			std::cout << c;
		}	
		
		readmeStream.close();
		std::cout << std::endl;
	}

	else // Error
	{
		std::cerr << "Couldn't open README file to show instructions. Please read the README file for instructions" << std::endl;
	}
}

void init(void)
{
	// Applies mesh data to track
	track = new Mesh("Assets/track_triangulated.obj");

	// Sets default color to black
	glClearColor(0, 0, 0, 0);

	// Fixes z-buffer z-fighting
	glEnable(GL_DEPTH_TEST);

	// Enables smooth shading
	glEnable(GL_SMOOTH);

	// Enables lights 0 & 1
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	setLights();

	// Enable backface culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Change matrix mode to affect camera
	glMatrixMode(GL_PROJECTION);

	// Load identity to not stack multiple affects
	glLoadIdentity();

	// Set camera perspective
	gluPerspective(45, 1, 1, 500);
}

// Entry point of the project
int main(int argc, char** argv)
{
/*================================================
				GLUT COMMANDS BEGIN
================================================*/

	// Initiates GLUT
	glutInit(&argc, argv);

	// Handles how glut will display stuff
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	// Initial window size glut will use
	glutInitWindowSize(winSize[0], winSize[1]);

	// Window position
	glutInitWindowPosition(winPos[0], winPos[1]);

	// Creates window
	glutCreateWindow("Space Racer");

	// Prints instructions from README
	instructions();

	// Set initial state of GLUT
	init();

	// Calls all callback functions for the program.
	callBacks();

	// Fixes z-buffer
	glEnable(GL_DEPTH_TEST);

	// Enters the GLUT event processing loop
	glutMainLoop();

	return 0;
}
