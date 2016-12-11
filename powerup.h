#ifndef __POWERUP_H__	//guard against cyclic dependancy
#define __POWERUP_H__


#include<vector>
using namespace std;

class powerup{
public:
	powerup(float posX, float posZ);	//constructor
	void draw();


	float posX, posZ, boost, x, z;
	bool collided;


private:
	
};

#endif