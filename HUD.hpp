#ifndef HUD_HPP
#define HUD_HPP

#include <string>
using namespace std;

class HUD // Contains data for heads-up display
{
	public:
		string getTimeString(); // Get formatted string displaying time
		void addTime(float dt); // Add elapsed time to current time
		HUD(); // Constructor
		string getBestTimeStr();
		void saveTime(); // Save current elapsed time as best time
		float getBestTime() { return bestTime; }
		float getTime() { return mSecTime; }
		void resetTime() { mSecTime = 0; }
	
	private:
		/* Methods */
		void convTime(); // Creates time string from seconds value

		/* Properties */
		float mSecTime; // Elapsed time in milliseconds
		float bestTime; // Best time
		string timeStr; // Time as a string
		string bestTimeStr;
};

#endif
