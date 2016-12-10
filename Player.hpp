#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

// INCLUDING LOCAL FILES
#include "Mesh.hpp"

// INCLUDING SYSTEM LIBRARIES
#include <math.h>
#include <string>

class Player
{

private:
	Mesh* ship;
	bool stillRacing;
	int penaltyCounter, health;
	float x, z, trackL, trackR;
	float rot[3];

public:
	Player(float posX, float posZ, float trackL, float trackR, std::string ship);
	~Player();
	
	float getX();
	float getZ();
	float getTrackL();
	float getTrackR();
	float getRotX();
	float getRotY();
	float getRotZ();
	void setRotX(float angle);
	void setRotY(float angle);
	void setRotZ(float angle);
	void velocity();
	void wallPenalty();
	void healthBar();
	Mesh* getShip() const;
};


#endif