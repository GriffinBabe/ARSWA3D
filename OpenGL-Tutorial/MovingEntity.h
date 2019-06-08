#ifndef MOVINGENTITY_H
#define MOVINGENTITY_H

#include "SolidEntity.h"

/**
	Extends SolidEntity, a moving entity is a solid entity that
	can move through different variables as speed, acceleration, gravity.
	A SolidEntity can be a Mob (character, npc) a projectile etc.

	@Author: Darius Couchard
*/

struct Speed {
	float dx = 0.0f;
	float dy = 0.0f;
};

class MovingEntity : public SolidEntity
{
public:

	MovingEntity(float x, float y);
	~MovingEntity();


	float getSpeedX() { return speedX; }
	float getSpeedY() { return speedY; }
	float getAcceleration() { return acceleration; }
	int getDirection() { return direction; }
	float getGravity() { return gravity; }

	void setSpeedX(float x) { speedX = x; }
	void setSpeedY(float y) { speedY = y; }

	/**
		This function is overriden by subclasses. Called when this entity hits another collidable entity.
		@param solidEntity, the entity we just hit.
	*/
	virtual void hit(SolidEntity* entity) = 0;

	/**
		Change the X speed depending the acceleration and direction.

		Also changes the rotation of the Model depending the direction.

		@param delta_time, the time that happened after the last call
		@returns speedX, the new speed.
	*/
	Speed accelerate(float delta_time);


	/**
		Changes the x and y position and returns a
		Position structure cotaning the new position
	*/
	Position move(float delta_time);

	/**
		Checks if this MovingEntity didn't crossed the map boundaries
	*/
	virtual void checkMapBoundaries(float bottom, float left, float right, float top) = 0;

protected:
	// Position from last loop, used to restore position when hitting another SolidEntity.
	float oldX = 0, oldY = 0;
	float speedX = 0, speedY = 0;
	float max_speed;
	int direction = 0; // -1 left 0 mid 1 right
	float acceleration;
	float gravity;

};

#endif