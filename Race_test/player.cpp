#include "player.h"
#include <stdio.h> 

#include <math.h>

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

player::player(float posX, float posZ, float trackR, float trackL){	//constructor
	x = posX;	
	z = posZ;
	track_sizeL = trackL;
	track_sizeR = trackR;
	health = 5;
	penaltyCounter = 0;
	prot[0] =0;
	prot[1] =0;
	prot[2] =0;
	stillRacing = true;
}

void player::draw(){
	if (stillRacing){
	glPushMatrix();
		float m_amb[] = {0.0,0.0,0.0,1.0};
		float m_diff[] = {0.1,0.1,0.1,1.0};
		float m_spec[] = {0.5,0.5,0.5,1.0};
		float shiny = 0.25 * 128;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
		glScalef(3, 0.8f, 3);
		glTranslatef(x, 1, z);
		glRotatef(prot[1],0,1,0);

		glPushMatrix();
			glRotatef(90,0,1,0);
			glutSolidTeapot(0.5);
		glPopMatrix();
	glPopMatrix();
	}
}

void player::wallPenalty(){
	if (stillRacing){
		if (x >= track_sizeL || x <= track_sizeR){
			x = posX;
			penaltyCounter += 1;
		}
	}
}

void player::velocity(){
	if(stillRacing){
		z -= (cos(prot[1]*M_PI/(180))*0.2); 
		x -= (sin(prot[1]*M_PI/(180))*0.2);
	}
}

void player::rotateLeft(){
	if(stillRacing){

	

	//float angle = M_PI/24;
	//x = x*cos(angle) - z*sin(angle);
	//z = z*cos(angle) + x*sin(angle);
	}
}

//void player::rotate(x1){
//	glRotatef(amount4.w + x1, amount4.x, amount4.y, amount4.z);
//}

void player::healthBar(){
	//if (health == 5){
	//	 g = 1;
	//}
	//else if (2 < health < 5){
	//	r = 1;
	//}
	//else if (health <= 2){
	//	g = 0;
	//}

	if(health <= 0){
		stillRacing = false;
	}
}
		