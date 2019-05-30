#pragma once

#include <vector>
#include "SolidEntity.h"
#include "Mob.h"


/*
* Manages the movement of the entities with the collisions
*/

class MovementManager
{
private:
	std::vector<SolidEntity*>* solid_entities = nullptr;

	// Map Boundaries
	float bottomMap;
	float leftMap;
	float rightMap;
	float topMap;

public:
	MovementManager();
	MovementManager(std::vector<SolidEntity*>* solid_entities, float bottom, float left, float right, float top);
	~MovementManager();

	void loop(float delta_time);
};

