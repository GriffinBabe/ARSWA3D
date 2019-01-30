#ifndef WITCH_H
#define WITCH_H

#include "Character.h"

class Witch : public Character
{
public:
	Witch(Game* map, float x, float y);
	~Witch();
};

#endif