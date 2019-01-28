#include "Character.h"


Character::Character(float x, float y,std::string path) : Entity(x, y, path)
{
	collidable = true;
}

Character::~Character()
{
}

void Character::loop(float delta_time)
{
	if (press_left && !press_right) {
		direction = -1;
	}
	else if (press_right && !press_left) {
		direction = 1;
	}
	else {
		direction = 0;
	}
	//Movement Loop
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

	if (press_up) {
		jump();
	}

	speedY += gravity * delta_time;

	float oldX = x; float oldY = y;

	x += speedX * delta_time;
	y += speedY * delta_time;

	if (y < 0) {
		y = 0;
		speedY = 0;
		jumps = max_jumps;
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
}

void Character::change_direction(int direction)
{
	this->direction = direction;
}

void Character::set_press_left(bool b)
{
	press_left = b;
}

void Character::set_press_right(bool b)
{
	press_right = b;
}

void Character::set_press_up(bool b)
{
	press_up = b;
}

void Character::jump()
{
	if (jumps > 0) {
		std::cout << "I jumped" << std::endl;
		speedY = jump_speed;
		jumps--;
	}
}
