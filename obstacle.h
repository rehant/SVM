#ifndef __OBSTACLE_H__	//guard against cyclic dependancy
#define __OBSTACLE_H__

//#include "player.h"
#include<vector>
using namespace std;

class obstacle{
public:
	obstacle(float posX, float posZ );	//constructor
	void draw();

	float posX, posZ, drop, x, z;


private:
	
};

#endif