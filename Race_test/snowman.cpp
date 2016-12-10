/* Snowman sample 
 * by R. Teather
 * Edited by Noel Brett
 */

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include "player.h"

//float verts[8][3] = { {-1,-1,1}, {-1,1,1}, {1,1,1}, {1,-1,1}, {-1,-1,-1}, {-1,1,-1}, {1,1,-1}, {1,-1,-1} };
float cols[6][3] = { {1,0,0}, {0,1,1}, {1,1,0}, {0,1,0}, {0,0,1}, {1,0,1} };
player player1 = player(1,1,-4.4,4.4);
float pos[] = {0,1,0};
float rot[] = {0, 0, 0};
float headRot[] = {0, 0, 0};

/*** 
 EYE LOCATION
 ***/
float eye[]{0,20,20};


float angle = 0.0f;

/* drawPolygon - takes 4 indices and an array of vertices
 *   and draws a polygon using the vertices indexed by the indices
 */
void drawPolygon(int a, int b, int c, int d, float v[8][3]){
	glBegin(GL_POLYGON);
		glVertex3fv(v[a]);
		glVertex3fv(v[b]);
		glVertex3fv(v[c]);
		glVertex3fv(v[d]);
	glEnd();
}

/* cube - takes an array of 8 vertices, and draws 6 faces
 *  with drawPolygon, making up a box
 */
void cube(float v[8][3])
{
	//front face	
	//glColor3fv(cols[1]);
	//drawPolygon(0, 3, 2, 1, v);
	
	//left wall
	glColor3fv(cols[2]);
	drawPolygon(1, 0, 4, 5, v);
	
	//topground
	glColor3fv(cols[3]);
	drawPolygon(5, 1, 2, 6, v);

	//right wall
	glColor3fv(cols[4]);
	drawPolygon(2, 3, 7, 6, v);
	
	//back face
	//glColor3fv(cols[5]);
	//drawPolygon(6, 5, 4, 7, v);

	//bottom ground
	//glColor3fv(cols[0]);
	//drawPolygon(4, 0, 3, 7, v);
}

/* drawBox - takes centre point, width, height and depth of a box,
 *  calculates its corner vertices, and draws it with the cube function
 */
void drawBox(float* c, float w, float h, float d)
{
	float vertices[8][3] = { {c[0]-w/2, c[1]-h/2, c[2]+d/2},
				 {c[0]-w/2, c[1]+h/2, c[2]+d/2},
				 {c[0]+w/2, c[1]+h/2, c[2]+d/2},
				 {c[0]+w/2, c[1]-h/2, c[2]+d/2}, 
				 {c[0]-w/2, c[1]-h/2, (c[2]-d/2)*4}, 
				 {c[0]-w/2, c[1]+h/2, (c[2]-d/2)*4}, 
				 {c[0]+w/2, c[1]+h/2, (c[2]-d/2)*4},
				 {c[0]+w/2, c[1]-h/2, (c[2]-d/2)*4} };

	cube(vertices);
}

bool keysDown[256];

void keyUp(unsigned char key, int x, int y)
{
	keysDown[key] = false;	
}

void keyboard(unsigned char key, int x, int y)
{	
	float dt = 10;
	keysDown[(int)key] = true; // This key is down

	if (keysDown[97] && keysDown[119]) // A & W are true, both are down
	{
		printf("W & A down\n");
	}

	/* key presses move the cube, if it isn't at the extents (hard-coded here) */
	switch (key)
	{
		case 'q':
		case 27:
			exit (0);
			break;

		case 'a':
		case 'A':
			if(pos[0] > -4.4)
				pos[0] -= 0.5;
				player1.prot[1]+=7.5;
			rot[1] = 180;
			break;

		case 'w':
		case 'W':
			if(pos[2] > -18)
				pos[2] -= 0.5;
				player1.velocity();
			rot[1] = 180;
			break;

		case 'd':
		case 'D':
			if(pos[0] < 4.4)
				pos[0]+=0.5;
			rot[1] = 180;
			break;

		case 's':
		case 'S':
			if(pos[2] < 4.4)
				pos[2] += 0.5;
				
			rot[1] = 0;
			break;

		case 'y':
		case 'Y':
			if(headRot[1] < 85)
				headRot[1] += 1;
			break;

		case 'u':
		case 'U':
			if(headRot[1] > -85)
				headRot[1] -= 1;
			break;
			
	}
	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	/* arrow key presses move the camera */
    /************************************************************************
     
                        CAMERA CONTROLS
     
     ************************************************************************/
	switch(key)
	{

	case 
	GLUT_KEY_LEFT: eye[0]-=0.5;
 	break; 
	case 
	GLUT_KEY_RIGHT: eye[0]+=0.5; 
	break;

	case
	GLUT_KEY_UP: eye[2]-=0.5;
 	break; 
	case 
	GLUT_KEY_DOWN: eye[2]+=0.5; 
	break;
	
	case
	GLUT_KEY_HOME: eye[1]-=0.5;
	break;
	case
	GLUT_KEY_END: eye[1] += 0.5;
	break;
	
		
    }
	glutPostRedisplay();
}

void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);
    	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);
    
    /************************************************************************
     
                            PERSPECTIVE SET UP!
     
     modelview moves the eye and objects, projection is for camera type
     frustum / ortho left, right, bottom, top, nearVal, farVal
     
     ************************************************************************/
    

}

void DrawSnowman(float* pos, float* rot)
{
	glPushMatrix();

	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(rot[1], 0, 1, 0);

	//draw body
	glColor3f(1,1,1);
	glutSolidSphere(1, 16, 16);

	//draw buttons
	glPushMatrix();
	glTranslatef(0, 0.35, 0.9);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.15, 0.95);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.05, 0.95);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();


	glPushMatrix();
	//translate relative to body, and draw head
	glTranslatef(0, 1.25, 0);
	glRotatef(headRot[1], 0, 1, 0); //turn the head relative to the body
	glColor3f(1,1,1);
	glutSolidSphere(0.5, 16, 16);
	
	//translate and draw right eye
	glPushMatrix();
	glTranslatef(0.2, 0.15, 0.45);
	glColor3f(0,0,1);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	//translate and draw left eye
	glPushMatrix();
	glTranslatef(-0.2, 0.15, 0.45);
	glColor3f(1,0,0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	//translate and draw nose
	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	glColor3f(1,0.4,0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	glPopMatrix();//body
	glPopMatrix();//snowman
}


/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{
	float origin[3] = {0,0,0};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /************************************************************************
     
                                    CAMERA SET UP
     
     ************************************************************************/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], 0, 0, 0, 0, 1, 0);	

	drawBox(origin, 10, 1, 10); //draws floor
	DrawSnowman(pos, rot);
	player1.draw();
	glutSwapBuffers();
	glutPostRedisplay();
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Snowman Example");	//creates the window

	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(special);

	glEnable(GL_DEPTH_TEST);
	init();

	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}
