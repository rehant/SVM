///**
//* This file is meant to test the Mesh class.
//**/
//
///* Standard includes */
//#include <iostream>
//
///* My includes */
//#include "Mesh.hpp" // Mesh class
//
//int main()
//{
//	Mesh cube("Assets/cube.obj"); // Try to load the file
//	Mesh track("Assets/track_triangulated.obj");
//	return 0;
//}

#include <stdio.h>
#include <stdlib.h> // atexit

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

// STL
#include <iostream>
 // cout, cin
#include <fstream> // ifstream
#include <vector>
using namespace std;

// Our classes
#include "Mesh.hpp"
#include "Material.hpp"

/* Camera */
float camPos[] = {0, 40, 10};	//where the camera is
float tarPos[] = {0, 0, 0};	//where that camera is pointed at
float camUp[] = {0, 1, 0};
float camSpeed = 0.4;
float camRot[] = {0, 0, 0};
float camRotDelta = 10;
bool shouldRotate = false;
Mesh* track = NULL; // Track mesh

//OpenGL functions
void keyboard(unsigned char key, int xIn, int yIn)
{
	switch (key)
	{
	}

	glutPostRedisplay();
}

void drawMesh(Mesh *m)
{
	vector<Face3D> mfaces = m->getFaces(); // Get a list of the mesh's faces
	vector<Vertex3D> mverts = m->getVerts(); // Fetch vertices
	vector<Vertex2D> mtverts = m->getTexVerts(); // Fetch texture vertices
	vector<Vec3D> mnorms = m->getNorms(); // Normals
	Material *faceMaterial; // Stores the face's material
	string curMatName = ""; // Stores the name of the current material (to avoid fetching materials which we're already using)
	Vertex3D curVert;
	Vec3D curNorm;
	Vertex2D curTexVert;
	
	cout << "Fetched mesh data" << endl;

	glBegin(GL_TRIANGLES); // Start drawing triangles

	for (int f = 0; f < mfaces.size(); f++)
	{
		cout << "Face #" << f+1 << endl;

		int vinds[3]; // Array of vertex indices
		int ninds[3]; // Array of normal indices
		int tinds[3]; // Array of texture indices
		Face3D curFace = mfaces.at(f); // Fetch the current face
		
		cout << "\tFetched face" << endl;

		if (curFace.getMatID() != curMatName) // Face uses a different material
		{	
			curMatName = curFace.getMatID(); // Fetch the material ID so that the comparison will fail the next time (and so that we can fetch the material object)
			cout << "\tcurMatName = \"" << curMatName << "\"" << endl;
			faceMaterial = new Material(m->getMaterial(curMatName));
			cout << "\tFetched material " << curMatName << endl;
		
			
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
			cout << "\tNo need to fetch, material name = \"" << curMatName << "\"" << endl;
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

		cout << "\tVertex indices = " << vinds[0] << ", " << vinds[1] << ", " << vinds[2] << endl;
		cout << "\tNormal indices = " << ninds[0] << ", " << ninds[1] << ", " << ninds[2] << endl;
		cout << "\tTexture indices = " << tinds[0] << ", " << tinds[1] << ", " << tinds[2] << endl;

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
		delete faceMaterial;

	glEnd(); // End triangles
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // Load an identity
	gluLookAt(camPos[0], camPos[1], camPos[2],
		tarPos[0], tarPos[1], tarPos[2],
		camUp[0], camUp[1], camUp[2]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Rotate camera
	/*glRotatef(-camRot[0], 1.0, 0.0, 0.0);
	glRotatef(-camRot[1], 0.0, 1.0, 0.0);
	glRotatef(-camRot[2], 0.0, 0.0, 1.0);*/

	drawMesh(track);

	glutSwapBuffers();
}

void special(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_UP:
		{
			if (camRot[0] < 180) // Don't let camera rotate more than 180 degrees
			{
				camRot[0] += camRotDelta;
			}
			break;
		}

		case GLUT_KEY_DOWN:
		{
			if (camRot[0] > -180)
			{
				camRot[0] -= camRotDelta;
			}

			break;
		}

		case GLUT_KEY_LEFT:
		{
			camRot[1] -= camRotDelta;
			break;
		}

		case GLUT_KEY_RIGHT:
		{
			camRot[1] += camRotDelta;
			break;
		}

		case 'z':
		case 'Z':
		{
			camRot[2] -= camRotDelta;
			break;
		}

		case 'x':
		case 'X':
		{
			camRot[2] += camRotDelta;
			break;
		}
	}

	shouldRotate = true;
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(45, w, 100, h); // Used for 2D projection
	gluPerspective(45, (float)((w+0.0f)/h), 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);
}

void cleanup()
{
	if (track != NULL)
	{
		delete track;
		track = NULL;
	}
}

void callBacks()
{
	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutReshapeFunc(reshape);
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
	instructions(); // SHow instructions

	/* Graphics setup */
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

    /* Light params */
	float pos[4] = {2, 10, 2, 1};
	//float amb[4] = {1, 1, 1, 1};
	float amb[4] = {0.5, 0.5, 0.5, 0.5};
	float dif[4] = {1, 0, 0, 1};
	float spc[4] = {0, 0, 1, 1};

    /* Create light 0 - upload data to GPU */
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spc);

	/** Light 1 **/
	float l2pos[4] = {100, 200, -60};
	float l2amb[4] = {0.8, 0.2, 0.3, 1};
	float l2dif[4] = {1, 0.4, 0.86, 1};
	float l2spc[4] = {0.5, 0.5, 1, 0.4};

	/* Create light 1 */
	glLightfv(GL_LIGHT1, GL_POSITION, l2pos);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l2dif);
	glLightfv(GL_LIGHT1, GL_AMBIENT, l2amb);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l2spc);
	track = new Mesh("Assets/track_triangulated.obj");
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // RGBA colspace & double buffering & depth channel enabled

    	/* Main window */
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Space Racer");	//creates the window
	init();
	callBacks(); // Register callbacks

	glutMainLoop();				//starts the event glutMainLoop
	return(0);					//return may not be necessary on all compilers
}
