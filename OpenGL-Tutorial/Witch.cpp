#include "Witch.h"



Witch::Witch(Game* game, float x, float y) : Character(game, x, y, ModelList::witch)
{
	health = 10;
	max_health = health;
	acceleration = 7.0f;
	gravity = -20.0f;
	jump_speed = 8.0f;
	max_speed = 5.0f;
	max_jumps = 1;
	jumps = max_jumps;

	// Collision box
	width = 0.5f;
	height = 1.2f;
	x_off = 0.0f;
	y_off = 0.6;
}


Witch::~Witch()
{
}
