#include "Witch.h"

Witch::Witch(float x, float y) : Character(x, y, ModelList::witch)
{
	Mob::health = 10;
	Mob::max_health = health;
	MovingEntity::acceleration = 7.0f;
	MovingEntity::gravity = -20.0f;
	Mob::jump_speed = 8.0f;
	Mob::max_jumps = 1;
	Mob::jumps = max_jumps;
	MovingEntity::max_speed = 3.0f;

	// Collision box
	SolidEntity::width = 0.5f;
	SolidEntity::height = 1.2f;
}


Witch::~Witch()
{
}
