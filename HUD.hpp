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
	
	private:
		/* Methods */
		void convTime(); // Creates time string from seconds value

		/* Properties */
		float mSecTime; // Elapsed time in milliseconds
		string timeStr; // Time as a string
};

#endif
