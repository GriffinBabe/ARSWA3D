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
	MovingEntity::max_speed = 8.0f;

	// Collision box
	Entity::width = 0.5f;
	Entity::height = 1.2f;
	SolidEntity::x_off = 0.0f;
	SolidEntity::y_off = 0.6f;
}


Witch::~Witch()
{
}
