#ifndef __TRACKINGCAMERA_HPP__
#define __TRACKINGCAMERA_HPP__

#include "Camera.hpp" // Parent
#include "Point3D.hpp"
#include "Vec3D.hpp"
#include "Player.hpp" // Tracking
#include "funcs.hpp" // movePoint

class TrackingCamera : public Camera
{
	public:
		TrackingCamera(Point3D pos, Player* p, Vec3D up); // Need the other data for the base class, need p to see
		void update(); // Updates target to track player
		~TrackingCamera(); // Destructor
		
		/** Getters **/
		float getPosX();
		float getPosY();
		float getPosZ();
		float getUpX();
		float getUpY();
		float getUpZ();
		float getTargX();
		float getTargY();
		float getTargZ();

		/** Camera control **/
		void move(float xAmt, float yAmt, float zAmt);

	private:
		Player* p; // Stores pointer to player object (so that we can track it)
		Vec3D* dVec; // Vector from our position to the player's position
};

#endif
