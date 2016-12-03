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

#include <iostream> // cout, cin
#include <fstream> // ifstream
#include <list> // list

/* My headers */
#include "SceneNode.hpp" // SceneNode
#include "GeometryNode.hpp" // GeometryNode
#include "ScaleNode.hpp"
#include "RotationNode.hpp"
#include "TranslateNode.hpp"

/* Camera */
float camPos[] = {30, 100, 20};	//where the camera is
float tarPos[] = {0, 0, 0};	//where that camera is pointed at
float camUp[] = {0, 1, 1};
float camSpeed = 0.4;
float camRot[] = {0, 0, 0};
float camRotDelta = 10;
bool shouldRotate = false; // Whether or not camera should be rotated

/* Scene graph */
SceneNode* root = NULL; // Root of scene

//OpenGL functions
void keyboard(unsigned char key, int xIn, int yIn)
{
	switch (key)
	{
	}

	glutPostRedisplay();
}

// Draws a particular node, and all of its children
void drawNode(SceneNode* node)
{
	list<SceneNode*> cl = node->getChildList(); // Store child list
	clog << "drawNode called" << endl;

	switch (node->getType()) // Check what type the node has
	{
		case 0: // Generic scene node
		{
			// Don't do anything for this
			break;
		}

		case 1: // Rotation node
		{
			RotationNode *rnod = reinterpret_cast<RotationNode*>(node);
			glRotatef(rnod->getXRot(), 1.0, 0.0, 0.0);
			glRotatef(rnod->getYRot(), 0.0, 1.0, 0.0);
			glRotatef(rnod->getZRot(), 0.0, 0.0, 1.0);
			break;
		}

		case 2: // Scale node
		{
			ScaleNode* snod = reinterpret_cast<ScaleNode*>(node);
			glScalef(snod->getXScale(), snod->getYScale(), snod->getZScale()); // Scale by specified amounts
			break;
		}

		case 3: // Translate node
		{
			TranslateNode* tnod = reinterpret_cast<TranslateNode*>(node); 
			glTranslatef(tnod->getX(), tnod->getY(), tnod->getZ()); // Translate 
			break;
		}

		case 4: // Geometry node
		{
			GeometryNode *gnod = reinterpret_cast<GeometryNode*>(node); // Convert to geometry node

			switch (gnod->getGeom()) // Check what this is
			{
				case TEAPOT: // Draw a teapot
				{
					clog << "Drawing teapot" << endl;
					glutSolidTeapot(3); // Draw a teapot
					break;
				}

				default:
				{
					clog << "Unknown geometry type" << gnod->getGeom() << endl;
					 break;
				}
			}
			break;
		}
	}

	for (list<SceneNode*>::iterator i = cl.begin(); i != cl.end(); i++) // Loop through children
	{
		drawNode(*i); // Draw them next
	}
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(camPos[0], camPos[1], camPos[2],
        tarPos[0], tarPos[1], tarPos[2],
        camUp[0], camUp[1], camUp[2]);

	//drawNode(root); // Start by drawing the root node	

  glutSwapBuffers();
  glEnd();
}

void special(int key, int x, int y)
{
	switch (key)
	{

	}

	//glutPostRedisplay();
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
	if (root != NULL)
	{
		delete root; // Delete top node of tree
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

	/* GL setup */
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);

	glEnable(GL_DEPTH_TEST); // Turn on depth test

	/* Lighting */
	glEnable(GL_LIGHTING); // Turn on lighting
	glEnable(GL_LIGHT0); // Turn on light 0
	glEnable(GL_LIGHT1); // TUrn on light 1

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

	/** Define and use a material **/
	float m_amb[] = {0.33, 0.22, 0.03, 1.0};
	float m_dif[] = {0.78, 0.57, 0.11, 1.0};
	float m_spec[] = {0.99, 0.91, 0.81, 1.0};
	float shiny = 10; // 10, 100

    // Upload material data to GPU
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

	// Define smooth (Gouraud) or flat shading
	glShadeModel(GL_SMOOTH);

	/* Backface culling */
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	// Testing: add to SceneNode
	root = new SceneNode();
	root->addChild(new GeometryNode(TEAPOT)); // Add a teapot to the root as a test

	callBacks(); // Register callbacks
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // RGBA colspace & double buffering & depth channel enabled

    /* Main window */
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Object Modeller");	//creates the window
	init();

	glutMainLoop();				//starts the event glutMainLoop
	return(0);					//return may not be necessary on all compilers
}
