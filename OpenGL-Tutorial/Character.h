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

protected:
	int health;
	int max_health;
	float acceleration;
	float gravity; // independant for each character
	float speedX = 0, speedY = 0;
	float max_speed;
	int direction = 0; // -1 left 0 mid 1 right
	int jumps;
	int max_jumps;
};
#endif