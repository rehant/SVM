// Main file for the project

// INCLUDING LOCAL FILES
#include "Player.hpp"

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

Player::Player(float x, float z, float trackL, float trackR, std::string ship)
{
	this->x = x;
	this->z = z;
	this->trackL = trackL;
	this->trackR = trackR;
	this->ship = new Mesh(ship);
	penaltyCounter = 0;
	health = 5;
	rot[0] = 0;
	rot[1] = 0;
	rot[2] = 0;
	stillRacing = true;
}

Player::~Player()
{
	delete ship;
}

// Getters
float Player::getX()
{
	return x;
}

float Player::getZ()
{
	return z;
}

float Player::getTrackL()
{
	return trackL;
}

float Player::getTrackR()
{
	return trackR;
}

float Player::getRotX()
{
	return rot[0];
}

float Player::getRotY()
{
	return rot[1];
}

float Player::getRotZ()
{
	return rot[2];
}

void Player::setRotX(float angle)
{
	rot[0] += angle;
}

void Player::setRotY(float angle)
{
	rot[1] += angle;
}

void Player::setRotZ(float angle)
{
	rot[2] += angle;
}

// Returns pointer to ship mesh
Mesh* Player::getShip() const
{
	return ship;
}

// Calculates ship position based on angle of rotation
void Player::velocity()
{
	if(stillRacing)
	{
		z -= (cos(rot[1]*M_PI/180)*0.2);
		x -= (sin(rot[1]*M_PI/180)*0.2);
	}
}

void Player::wallPenalty()
{
	if (stillRacing)
	{
		if (x >= trackL || x <= trackR)
		{
			penaltyCounter += 1;
		}
	}
}

void Player::healthBar()
{
	if(health <= 0)
	{
		stillRacing = false;
	}
}