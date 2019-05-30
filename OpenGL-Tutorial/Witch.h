#ifndef WITCH_H
#define WITCH_H

#include "Character.h"

/**
	Final class, extends Character. 
	Is a one of many Character classes.
	Here are defined the values of the Witch as a mob, moving, solid entity.

	@Author Darius Couchard
*/

class Witch : public Character
{
public:
	Witch(float x, float y);
	~Witch();
};

#endif