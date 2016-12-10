#ifndef __POWERUP_H__	//guard against cyclic dependancy
#define __POWERUP_H__

//#include "player.h"
#include<vector>
using namespace std;

class powerup{
public:
	powerup(float posX, float posZ /*player* player*/);	//constructor
	void draw();
	//void collision();
	//void speedBoost();

	float posX, posZ, boost, x, z;
	bool collided;
	//player* player1;


private:
	
};

#endif