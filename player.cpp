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
	stillRacing = true;
	speed = 0.2;
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
			glutSolidCube(1);
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
		z -= speed;
	}
}

void player::rotateLeft(float dt){
	if(stillRacing){
	x += -sin((x * M_PI ) / 180) * 0.02 *dt;
	}
}

void player::healthBar(){
	if(health <= 0){
		stillRacing = false;
	}
}

float player::getHealth()
{
	return health;
}

float player::getMaxHealth()
{
	//printf("getMaxHealth called\n");
	return 5;
}

void player::decHealth()
{
	health -= 0.1;
	//printf("decHealth called\n");
}
