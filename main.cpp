// Main file for the project

// INCLUDING LOCAL FILES
#include "Mesh.hpp"
#include "Player.hpp"
#include "Material.hpp"
#include "Point3D.hpp"
#include "Face3D.hpp"
#include "Vec3D.hpp"
#include "Point2D.hpp"
#include "obstacle.h"
#include "powerup.h"
#include "HUD.hpp"

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

bool keysDown[256]; // Boolean array for keys
float alpha = 7.5;	// Angle of ship rotation along y-axis

float camPos[] 	= {0, 75, 10};		// Position of camera
float tarPos[] = {0, 0, 0};			//where that camera is pointed at
float camUp[] = {0, 1, 0};

float lightPos0[] = {2, 10, 2, 1};		// Position of light0
float lightPos1[] = {100, 200, -60, 1};	// Position of light1

// Overhead light paramter arrays (RGBA)
float amb_l[]	= {1, 1, 1, 1};
float diff_l[]	= {1, 1, 1, 1};
float spec_l[]	= {1, 1, 1, 1};

// Headlight parameter arrays (RGBA)
float amb_h[]	= {0, 0, 1, 1};
float diff_h[]	= {0, 0, 1, 1};
float spec_h[]	= {0, 0, 1, 1};

/* Track */
float trackPos[] = {0, 0, 0};
int angle = 0;
float xangle = 0;

// Init track pointer
Mesh* track = NULL;
Player* player = NULL;

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

HUD hud;


/*================================================
				DRAW METHODS
================================================*/

/**
* Draws a string in OpenGL.
* @param s The string to draw
* @param x X position
* @param y Y position
*/
void drawString(int x, int y, string s)
{
	void* font = GLUT_BITMAP_9_BY_15;

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, winSize[0], 0.0, winSize[1]);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();	
	glColor3f(0.0, 1.0, 0.0); // Font colours (green)
	glDisable(GL_LIGHTING);

	glRasterPos2i(x, y); // Set text position

	for (string::iterator i = s.begin(); i != s.end(); ++i)
	{
		//glutStrokeCharacter(GLUT_STROKE_ROMAN, *c); // Draw the character
		glutBitmapCharacter(font, *i);
	}

	/* Restore matrices */
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void drawHealthBar()
{
	Point2D topLeft(600, 540);
	Point2D botLeft(600, 520);
	float pHealth = player->getHealth();
	float pMaxHealth = player->getMaxHealth();
	//clog << "main: pHealth = " << pHealth << ", pMaxHealth = " << pMaxHealth << endl;
	float pHP = 100*pHealth/pMaxHealth;
	//clog << "main: pHP = " << pHP << endl;
	Point2D topRight(600+pHP, 540);
	Point2D botRight(600+pHP, 520);
	Colour pCol; // Colour to use for health bar (depends on percentage of player health)

	/* Determine colour to use based on percentage of health remaining */
	if (pHP > 66) // > 2/3 left
	{
		/* Green */
		pCol.setR(0);
		pCol.setG(255);
		pCol.setB(0);
	}

	else if (pHP > 33) // > 1/3 left
	{
		/* Orange */
		pCol.setR(255);
		pCol.setG(140);
		pCol.setB(0);
	}

	else // < 1/3 left
	{
		/* Red */
		pCol.setR(255);
		pCol.setG(0);
		pCol.setB(0);
	}

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, winSize[0], 0.0, winSize[1]);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(0.0, 1.0, 0.0);
	glDisable(GL_LIGHTING);
	
	glBegin(GL_QUADS);
		glColor3f(pCol.getR(), pCol.getG(), pCol.getB());
		glVertex2f(botRight.getX(), botRight.getY());
		glVertex2f(topRight.getX(), topRight.getY());
		glVertex2f(topLeft.getX(), topLeft.getY());
		glVertex2f(botLeft.getX(), botLeft.getY());
		/*glVertex2f(700, 520);
		glVertex2f(700, 540);
		glVertex2f(600, 540);
		glVertex2f(600, 520);*/
	glEnd();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void drawHUD()
{
	/* Draw time */
	string tmstr = hud.getTimeString();
	int slen = tmstr.length();
	int mod = 4;
	int sx = 600;
	int sy = 550;
	//cout << "String pos = (" << sx << ", " << sy << ")" << endl;
	drawString(sx, sy, tmstr);

	drawHealthBar();
}

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

// Enables headlight
void setHeadLight(float x, float y, float z)
{
	// Initialize a headlight at specified postion
	float headlight[] = {x, y, z, 1};
	// Enable the light to turn on
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_POSITION, headlight);
	glLightfv(GL_LIGHT2, GL_AMBIENT, amb_h);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diff_h);
	glLightfv(GL_LIGHT2, GL_SPECULAR, spec_h);
}

// Draws the object
void drawMesh(Mesh* m)
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

void renderShip()
{
	// SHIP CODE
	glPushMatrix();
		// Set initial position of our ship to origin on top of track
		glTranslatef(player->getX(), 0, player->getZ());

		// Enable rotation of rot[1] degrees at the origin along the y-axis for the ship
		glRotatef(player->getRotY(), 0, 1, 0);

		// Draws ship from player object
		drawMesh(player->getShip());

		// Draws the headlight
		setHeadLight(1,2,0);
		glTranslatef(1,2,0);
		glutSolidCube(0.2f);
	glPopMatrix();
}

// Deletes objects on exit
void cleanup()
{
	if (track != NULL)
	{
		delete track;
		track = NULL;
	}
	if (player != NULL)
	{
		delete player;
		player = NULL;
	}
}

/*================================================
			OPENGL & GLUT DEFINED METHODS
================================================*/
void keyUp(unsigned char key, int x, int y)
{
	keysDown[key] = false;
}

void keyboard(unsigned char key, int xIn, int yIn)
{
	keysDown[(int)key] = true; // If true then this key is down

	if (keysDown[97] && keysDown[119]) // If A & W are true then both keys are pressed
	{
		player->velocity();
		player->setRotY(alpha);
	}

	if (keysDown[100] && keysDown[119]) // If D & W are true then both keys are pressed
	{
		player->velocity();
		player->setRotY(-alpha);
	}

	switch(key)
	{
		case 27:
			exit(0);
			break;

		// Rotates player left
		case 'a':
		case 'A':
			player->setRotY(alpha);
			//cout << player->getRotY() << endl;
			break;

		// Rotates player right
		case 'd':
		case 'D':
			player->setRotY(-alpha);
			//cout << player->getRotY() << endl;
			break;

		// Moves player forward by updating {x,z} along their angle
		case 'w':
		case 'W':
			player->velocity();
			break;

		case 's':
		case 'S':
			break;

		case 'p':
		case 'P': // Test - decrement player health and update hud
		{
			player->decHealth();
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
		//glTranslatef(tarPos[0], tarPos[1], tarPos[2]);
		//glRotatef(angle, 0.0, 1.0, 0.0);
		//glTranslatef(-tarPos[0], -tarPos[1], -tarPos[2]);

		// Draws track
		drawMesh(track);
		//glRotatef(90,0,1,0);

		// Renders Ship
		renderShip();

		// Draws power ups
		powerup1.draw();
		powerup2.draw();
		powerup3.draw();
		
		// Draws obstacles
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

	drawHUD();

	// Swap into back buffer on each call to display 
	glutSwapBuffers();

	// Redisplay the screen
	glutPostRedisplay();
}

void callBacks(void)
{
	// Runs display callback function
	glutDisplayFunc(display);

	// Runs keyboard callback function. Allows for keyboard input
	glutKeyboardFunc(keyboard);

	// Releases key presses
	glutKeyboardUpFunc(keyUp);

	// Runs special callback function. Allows for special keyboard inputs
	glutSpecialFunc(special);

	// Runs mouse callback function. Allows for mouse inputs
	glutMouseFunc(mouse);

	// Cleans up memory
	atexit(cleanup);
}

void init(void)
{
	// Applies mesh data to track
	track = new Mesh("Assets/track_triangulated.obj");

	// Applies mesh data to ship, and creates a player using ship object
	player = new Player(1, 1, -5, 5, "Assets/ship_triangulated.obj");

	// Sets default color to black
	glClearColor(0, 0, 0, 0);

	// Fixes z-buffer z-fighting
	glEnable(GL_DEPTH_TEST);

	// Enables smooth shading
	glEnable(GL_SMOOTH);

	// Enables lights 0 & 1
	glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
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

void instructions()
{
	std::ifstream readmeStream("README", std::ifstream::in); // Open README file
	char c;

	if (readmeStream.is_open()) // Stream opened
	{
		while (readmeStream.good())
		{
			c = readmeStream.get();
			//std::cout << c;
		}	
		
		readmeStream.close();
		//std::cout << std::endl;
	}

	else // Error
	{
		std::cerr << "Couldn't open README file to show instructions. Please read the README file for instructions" << std::endl;
	}
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
