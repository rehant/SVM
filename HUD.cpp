#include "HUD.hpp"

/* STL */
#include <sstream>
using namespace std;

HUD::HUD()
{
	secTime = 0;
	convTime();
}

void HUD::addTime(float dt)
{
	secTime += dt;
	convTime();
}

string HUD::getTimeString()
{
	return timeStr;
}

void HUD::convTime()
{
	stringstream ss; // Stringstream for conversion
	float min = 0; // Minutes
	float tim = secTime; // Copy of time for subtraction

	/* Find # of minutes elapsed */
	while (tim >= 60) // Loop until remaining time < a minute
	{
		min++; // Increment # of minutes elapsed
		tim -= 60; // Subtract equivalent of 1 minute		
	}

	// tim now stores remaining # of seconds (< 60)
	ss << "Elapsed time: " << min << ":" << tim; // Construct string
	timeStr = ss.str(); // Store result
}
