#include "Mob.h"
#include <iostream>

Mob::Mob(float x, float y, Model * model) : MovingEntity(x,y,model)
{
}

Mob::~Mob()
{

}

void Mob::hit(SolidEntity* entity)
{
	// Si on est en train de tomber
	if (speedY < 0) {
		if (y - height / 2 + speedY < entity->y - entity->height / 2) {
			y = entity->y + entity->height / 2 + height / 2;
			speedY = 0;
			jumps = max_jumps;
		}
	}
	else if (speedY >= 0) {
		y = oldY;
		speedY = 0;
	}
	/*
				if p1Y + 64 + p1YS >= obstacle[0][1] and p1Y <= obstacle[0][1] and p1YS > 0:
						p1Y = obstacle[0][1] - 65
						p1YS = 0
						p1jumps = p1Attributes[3]

				elif p1Y + p1YS <= obstacle[0][1] + obstacle[1][1] and p1Y >= obstacle[0][1] and p1YS < 0:
					p1Y = obstacle[0][1] + obstacle[1][1]
					p1YS = 0

				else:
					if p1X+64 <= obstacle[0][0]+obstacle[1][0]:
						p1X = obstacle[0][0] - 64
						p1XS = 0
					if p1X >= obstacle[0][0]:
						p1X = obstacle[0][0] + obstacle[1][0]
						p1XS = 0
	if (speedY > 0) {
		y = oldY;
		speedY = 0;
	}
	if (speedY <= 0) {
		y = entity->y + entity->height / 2 + height / 2;
		speedY = 0;
	}
	x = oldX;
	speedX = 0;
	*/
	// TODO: Improve collision
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