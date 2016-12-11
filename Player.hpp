#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

// INCLUDING LOCAL FILES
#include "Mesh.hpp"
#include "BoundingSphere.hpp"

// INCLUDING SYSTEM LIBRARIES
#include <math.h>
#include <string>

class Player
{

private:
	Mesh* ship;
	bool stillRacing, collided;
	int penaltyCounter, health, speed;
	float x, y, z, trackL, trackR;
	float rot[3];
	BoundingSphere* bsp;

public:
	Player(float posX, float posZ, float trackL, float trackR, std::string ship);
	~Player();	

	float getX();
	float getY();
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
	void speedDrop();
	void speedBoost();
	Mesh* getShip() const;
	int getHealth();
	int getMaxHealth() const;	
	void decHealth();
	void setBoundingSphere(BoundingSphere* sp);
	void stop() { stillRacing = false; }
	void start() { stillRacing = true; }
};


#endif
