#ifndef __PLAYER_H__	
#define __PLAYER_H__

#include<vector>
#include "structs.h"
using namespace std;

class player{
public:
	player(float posX, float posZ, float trackL, float trackR);	//constructor
	void draw();
	void velocity();
	void wallPenalty();
	void healthBar();
	void rotateLeft(float dt);

	float x, z, track_sizeL, track_sizeR, posX, posZ, trackL, trackR,x1, speed;
	bool stillRacing;
	int penaltyCounter, health;
	Vector4D amount4;
private:
	
};

#endif