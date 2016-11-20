// Main file for the project

// INCLUDING LOCAL FILES
#include "Mesh.hpp"

// INCLUDING SYSTEM LIBRARIES
#include <string>

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

/*================================================
				GLOBALS VARIABLES
================================================*/
std::string TITLE = "Ships vs. Monsters"
int winPos[2] = {50,50};
int winSize[2] = {1280,720};

/*================================================
				DRAW METHODS
================================================*/
void drawFace(//vector of stuff as parameter)
{

}

void drawObject(Mesh* pmesh)
{
	glBegin(GL_TRIANGLES);
	/*
		mesh -> face vector
		for each face in vector(face)
			for each vertex in vector(vertex)
				draw the face here
	*/
	glEnd(GL_TRIANGLES);
}

/*================================================
			OPENGL & GLUT DEFINED METHODS
================================================*/

void keyboard(unsigned char key, int xIn, int yIn)
{
	switch(key)
	{
		case'q':
		case 27:
			exit(0);
			break;
	}
}



void special(int key, int x, int y)
{
	switch(key)
	{

	}
}

void mouse(int btn, int state, int x, int y)
{

}

void display(void)
{
	glutSwapBuffers();
}

void callbacks(void)
{
	// Runs display callback function
	glutDisplayFunc(display);

	// Runs keyboard callback function. Allows for keyboard input
	glutKeyboardFunc(keyboard);

	// Runs special callback function. Allows for special keyboard inputs
	glutSpecialFunc(special);

	// Runs mouse callback function. Allows for mouse inputs
	glutMouseFunc(mouse);
}

void init(void)
{
	// Sets default color to black
	glClearColor(0, 0, 0, 0);

	// Set color to white
	glColor3f(1, 1, 1);

	// Enable color on materials
	glEnable(GL_COLOR_MATERIAL);

		// Change matrix mode to affect camera
	glMatrixMode(GL_PROJECTION);

	// Load identity to not stack multiple affects
	glLoadIdentity();

	// Set camera perspective
	gluPerspective(45, 1, 1, 400);

	// Set faces to be shown if they're made counterclockwise
	glFrontFace(GL_CCW);

	// Cull backfaces
	glCullFace(GL_BACK);

	// Enable backface culling
	glEnable(GL_CULL_FACE);

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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Initial window size glut will use
	glutInitWindowSize(winSize[0], winSize[1]);

	// Window position
	glutInitWindowPosition(winPos[0], winPos[1]);

	// Creates window
	glutCreateWindow(TITLE);

	// Calls all callback functions for the program.
	callBacks();

	// Set initial state of GLUT
	init();

	// Fixes z-buffer
	glEnable(GL_DEPTH_TEST);

	// Enters the GLUT event processing loop
	glutMainLoop();

	return 0;
}