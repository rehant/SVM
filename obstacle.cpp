#include "obstacle.h"
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

obstacle::obstacle(float posX, float posZ /*player* player*/){	//constructor
	x = posX;
	z = posZ;	
	collided = false;
	//player1 = player;

}

void obstacle::draw(){
	if (collided == false){
		glPushMatrix();
			float m_amb[] = {0.2125,0.1275,0.054,1.0};
			float m_diff[] = {0.714,0.4284,0.18144,1.0};
			float m_spec[] = {0.393548,0.271906,0.166721,1.0};
			float shiny = 0.2 * 128;
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
			glScalef(1, 3, 1);
			glTranslatef(x, 0.85, z);
			glutSolidCube(1);
		glPopMatrix();
	}
}

//void obstacle::collision(){
//	if(x == player1->x && z == player1->z){
//		collided = true;	
//		printf("%f", 1);
//	}
	
//}

//void obstacle::speedDrop(){
//	if (collided = true){
//		player1->speed = player1->speed/2;
//		collided = false;
//	}
//}