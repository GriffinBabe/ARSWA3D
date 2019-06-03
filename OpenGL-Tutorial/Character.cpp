#include "Character.h"

Character::Character(float x, float y) : Mob(x,y)
{

}

Witch::Witch(float x, float y) : Character(x, y)
{

	Character::id = WITCH;

	Mob::health = 10;
	Mob::max_health = health;
	MovingEntity::acceleration = 7.0f;
	MovingEntity::gravity = -20.0f;
	Mob::jump_speed = 7.5f;
	Mob::max_jumps = 1;
	Mob::jumps = max_jumps;
	MovingEntity::max_speed = 3.0f;

	// Collision box
	SolidEntity::width = 0.35f;
	SolidEntity::height = 0.84f;

	Entity::scaleX = 0.7;
	Entity::scaleY = 0.7;
}


Witch::~Witch()
{
}
