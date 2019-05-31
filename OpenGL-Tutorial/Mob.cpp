#include "Mob.h"
#include <iostream>

Mob::Mob(float x, float y, Model * model) : MovingEntity(x,y,model)
{
}

void Mob::hit(SolidEntity* entity)
{
	// TODO: Improve collision
	if (speedY <= 0) {
		y = oldY;
		speedY = 0;
	}
	x = oldX;
	speedX = 0;
}

void Mob::checkMapBoundaries(float bottom, float left, float right, float top)
{
	if (y - height / 2 < bottom && speedY <= 0) {
		y = bottom + height/2;
		speedY = 0;
		jumps = max_jumps;
	}

	if (x + width / 2 > right || x - width / 2 < left) {
		x = oldX;
		speedX = 0;
	}

	if (y + height / 2 > top) {
		y = top;
	}
}

void Mob::jump()
{
	if (jumps > 0) {
		speedY = jump_speed;
		jumps--;
	}
}

void Mob::change_direction(int direct)
{
	direction = direct;
}