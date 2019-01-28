#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"

class Character : public Entity
{
public:
	Character(float x, float y, std::string path);
	~Character();

	void loop(float delta_time);

	void change_direction(int direction);
	void set_press_left(bool b);
	void set_press_right(bool b);
	void set_press_up(bool b);

	void jump();

protected:
	int health;
	int max_health;
	float acceleration;
	float gravity; // independant for each character
	float jump_speed;
	float speedX = 0, speedY = 0;
	float max_speed;
	int direction = 0; // -1 left 0 mid 1 right
	int jumps;
	int max_jumps;

	bool press_left = false;
	bool press_right = false;
	bool press_up = false;
};
#endif