#include "HUD.hpp"

/* STL */
#include <sstream>
using namespace std;

HUD::HUD()
{
	mSecTime = 0;
	bestTime = 0;
	convTime();
}

void HUD::addTime(float dt)
{
	mSecTime += dt;
	convTime();
}

string HUD::getTimeString()
{
	return timeStr;
}

void HUD::convTime()
{
	/* Current time */
	stringstream ss; // Stringstream for conversion
	float min = 0; // Minutes
	float tim = mSecTime; // Copy of time for subtraction
	float sec = 0; // Seconds

	/* Find # of minutes elapsed */
	while (tim >= 60000) // Loop until remaining time < a minute
	{
		min++; // Increment # of minutes elapsed
		tim -= 60000; // Subtract equivalent of 1 minute		
	}

	/* Find number of seconds elapsed */
	while (tim >= 1000) // Loop until remaining time < 1 second
	{
		sec++; // Inc # of seconds
		tim -= 1000; // Subtract equivalent of 1 second
	}

	// tim now stores remaining # of milliseconds (< 1000)
	ss << "Elapsed time: " << min << ":" << sec << ":" << tim; // Construct string
	timeStr = ss.str(); // Store result

	/* Best time */
	stringstream ss2; // Stringstream for conversion
	min = 0; // Minutes
	tim = mSecTime; // Copy of time for subtraction
	sec = 0; // Seconds

	/* Find # of minutes elapsed */
	while (tim >= 60000) // Loop until remaining time < a minute
	{
		min++; // Increment # of minutes elapsed
		tim -= 60000; // Subtract equivalent of 1 minute		
	}

	/* Find number of seconds elapsed */
	while (tim >= 1000) // Loop until remaining time < 1 second
	{
		sec++; // Inc # of seconds
		tim -= 1000; // Subtract equivalent of 1 second
	}

	// tim now stores remaining # of milliseconds (< 1000)
	ss2 << "Best time: " << min << ":" << sec << ":" << tim; // Construct string
	bestTimeStr = ss2.str(); // Store result
}

void HUD::saveTime()
{
	bestTime = mSecTime; // Save current time as best time
	convTime();
}

string HUD::getBestTimeStr()
{
	return bestTimeStr;
}
