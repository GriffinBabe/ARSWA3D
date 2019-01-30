#include "Character.h"
#include "Game.h"


Character::Character(Game* game, float x, float y, Model* model) : SolidEntity(x, y, model)
{
	this->game = game;
	this->map = this->game->get_map();
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

	if (y + y_off - height/2 < this->map->boundary_bottom && speedY <= 0) {
		y = this->map->boundary_bottom;
		speedY = 0;
		jumps = max_jumps;
	}

	if (x + x_off + width/2 > this->map->boudary_right || x - x_off - width/2 < this->map->boundary_left) {
		x = oldX;
		speedX = 0;
	}

	if (y + y_off + height/2 > this->map->boundary_top) {
		y = this->map->boundary_top;
	}

	for (SolidEntity* se : *this->map->get_collision_entities()) { // Solid Entities of the map (as platforms)
		if (check_collision(se, x, oldY)) { // Horizontal collision
			x = oldX;
			speedX = 0;
		}
		if (check_collision(se, oldX, y+y_off)) { // vertical collision
			if (speedY < 0) {
				jumps = max_jumps;
			}
			y = oldY;
			speedY = 0;
		}
	}
	for (SolidEntity* se : *this->game->getEntities()) { // Solid Entities of the game (as characters)
		if (se != this) { // We don't wanna collide on ourself
			if (check_collision(se, x, oldY)) { // Horizontal collision
				x = oldX;
				speedX = 0;
			}
			if (check_collision(se, oldX, y) && speedY <= 0) { // Vertical collision
				y = oldY;
				speedY = 0;
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

bool Character::check_collision(SolidEntity * entity, int x, int y) 
{
	//std::cout << entity->x << " " << entity->y << " " << entity->width << " " << entity->height << " " << entity->x_off << " " << entity->y_off << std::endl;
	if (x + x_off + width / 2 > entity->x - entity->x_off - entity->width / 2 &&
		x - x_off - width / 2 < entity->x + entity->x_off + entity->width / 2 &&
		y + y_off - height / 2 < entity->y + entity->y_off + entity->height / 2 &&
		y + y_off + height / 2 > entity->y + entity->y_off + entity->height / 2) {
			std::cout << "collision!" << std::endl;
			return true;
	}
	return false;
}
