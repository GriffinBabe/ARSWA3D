#include "Witch.h"



Witch::Witch(float x, float y) : Character(x, y, "Models/witch/witch-toon.obj")
{
	health = 10;
	max_health = health;
	acceleration = 7.0f;
	gravity = -20.0f;
	jump_speed = 8.0f;
	max_speed = 5.0f;
	max_jumps = 1;
	jumps = max_jumps;
}


Witch::~Witch()
{
}
