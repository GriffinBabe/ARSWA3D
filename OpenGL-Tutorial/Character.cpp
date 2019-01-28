#include "Character.h"


Character::Character(float x, float y,std::string path) : Entity(x, y, path)
{
}

Character::~Character()
{
}

void Character::loop(float delta_time)
{
	std::cout << direction << std::endl;
	//Movement Loop
	if (direction != 0) {
		if (std::abs(speedX += direction * acceleration * delta_time) < max_speed * delta_time) {
			speedX += acceleration * direction * delta_time;
		}
		else {
			speedX = max_speed * delta_time;
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
	speedY -= gravity * delta_time;

	float oldX = x; float oldY = y;

	x += speedX;
	//y += speedY;
}

void Character::change_direction(int direction)
{
	this->direction = direction;
}
