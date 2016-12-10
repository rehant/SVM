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

powerup::powerup(float posX, float posZ /*player* player*/){	//constructor
	x = posX;
	z = posZ;	
	collided = false;
	//player1 = player;

}

void powerup::draw(){
	if (collided == false){
		glPushMatrix();
			glScalef(1, 3, 1);
			glTranslatef(x, 0.85, z);
			glColor3f(0, 1, 0);
			glutWireCube(1);
		glPopMatrix();
	}
}

//void powerup::collision(){
//	if(x == player1->x && z == player1->z){
//		collided = true;	
//		printf("%f", 1);
//	}
	
//}

//void powerup::speedBoost(){
//	if (collided = true){
//		player1->speed = player1->speed*2;
//		collided = false;
//	}
//}