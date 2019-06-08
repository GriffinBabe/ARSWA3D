#ifndef MOB_H
#define MOB_H

#include "MovingEntity.h"

/**
	Extends MovingEntity and contains additional informations realted to Players ans NPCs

	@Author: Darius Couchard
*/

class Mob : public MovingEntity
{
public:
	Mob(float x,float y);
	~Mob();

	// Called when it hits again a solid entity
	void hit(SolidEntity* entity) final;

	/**
		Overrides the moving entity checkMapBoundaries as it has to take care of the jump.
	*/
	void checkMapBoundaries(float bottom, float left, float right, float top);

	// Jumps, chaning Yspeed
	void jump();
	void change_direction(int direct);

	int getHealth() { return health; }
	int getMaxHealth() { return max_health; }

protected:
	int health;
	int max_health;
	float jump_speed;
	int jumps;
	int max_jumps;
};


#endif