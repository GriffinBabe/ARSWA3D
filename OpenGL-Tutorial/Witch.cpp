#include "Witch.h"



Witch::Witch(float x, float y) : Character(x, y, "Models/witch/witch-toon.obj")
{
	health = 10;
	max_health = health;
	acceleration = 0.5f;
	gravity = 0.2f;
	max_speed = 1;
	max_jumps = 1;
	jumps = max_jumps;
}


Witch::~Witch()
{
}
