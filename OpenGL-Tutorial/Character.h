#ifndef CHARACTER_H
#define CHARACTER_H

#include "Mob.h"
#include "ModelList.h"
#include "Map.h"

class Game;

/**
	Extends mob and is extended by character classes
	(like witch, warrior...).

	@Author: Darius Couchard
*/

class Character : public Mob
{
public:
	Character(float x, float y, Model* model);

};
#endif