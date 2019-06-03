#ifndef CHARACTER_H
#define CHARACTER_H

#include "Mob.h"
#include "ModelList.h"
#include "Map.h"

class Game;


enum CharacterID {
	WITCH,
};

/**
	Extends mob and is extended by character classes
	(like witch, warrior...).

	@Author: Darius Couchard
*/

class Character : public Mob
{
public:
	Character(float x, float y);


	CharacterID id;
};

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