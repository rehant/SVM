#ifndef __OBSTACLE_H__	//guard against cyclic dependancy
#define __OBSTACLE_H__

//#include "player.h"
#include<vector>
using namespace std;

class obstacle{
public:
	obstacle(float posX, float posZ /*player* player*/);	//constructor
	void draw();
	//void collision();
	//void speedDrop();

	float posX, posZ, drop, x, z;
	bool collided;
	//player* player1;


private:
	
};

#endif