#include "powerup.h"
#include <stdio.h> //needed for printf command
//#include "player.h"

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

powerup::powerup(float posX, float posZ){	//constructor
	x = posX;
	z = posZ;	
}

void powerup::draw(){
	//if (collided == false){
		glPushMatrix();
			glScalef(1, 3, 1);
			glTranslatef(x, 1, z);
			glColor3f(0, 1, 0);
			glutWireCube(1);
		glPopMatrix();
	//}
}

