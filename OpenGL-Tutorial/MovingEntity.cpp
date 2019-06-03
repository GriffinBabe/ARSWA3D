#include "MovingEntity.h"

MovingEntity::MovingEntity(float x, float y) : SolidEntity(x,y,)
{
}

MovingEntity::~MovingEntity()
{
}

Speed MovingEntity::accelerate(float delta_time)
{
	if (direction != 0) {
		if (std::abs(speedX += direction * acceleration * delta_time) < max_speed) {
			speedX += acceleration * direction * delta_time;
		}
		else {
			speedX = direction * max_speed;
		}
	}
	else {
		if (speedX > 0) {
			if (speedX - acceleration * delta_time > 0) {
				speedX -= acceleration * delta_time;
			}
			else {
				speedX = 0;
			}
		}
		else if (speedX < 0) {
			if (speedX + acceleration * delta_time < 0) {
				speedX += acceleration * delta_time;
			}
			else {
				speedX = 0;
			}
		}
	}

	//rotation
	if (direction > 0) {
		rotY = 90.0;
	}
	else if (direction < 0) {
		rotY = -90.0;
	}
	else {
		rotY = 0.0f;
	}

	speedY += gravity * delta_time;

	Speed newSpeed;
	newSpeed.dx = speedX;
	newSpeed.dy = speedY;
	return newSpeed;
}

Position MovingEntity::move(float delta_time)
{
	oldX = x;
	oldY = y;

	x += speedX * delta_time;
	y += speedY * delta_time;

	Position newPosition;
	newPosition.x = x;
	newPosition.y = y;
	return newPosition;
}