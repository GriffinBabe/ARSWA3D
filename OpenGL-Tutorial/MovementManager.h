#ifndef MOVEMENTMANAGER_H
#define MOVEMENTMANAGER_H

#include <vector>
#include "SolidEntity.h"
#include "Mob.h"


/*
* Manages the movement of the entities with the collisions
*/

class MovementManager
{
private:

	// Map Boundaries
	float bottomMap;
	float leftMap;
	float rightMap;
	float topMap;

public:
	MovementManager();
	MovementManager(float bottom, float left, float right, float top);
	~MovementManager();

	void loop(std::vector<Entity*>* entities, float delta_time);
};

#endif