#ifndef WITCH_H
#define WITCH_H

#include "Character.h"

class Witch : public Character
{
public:
	Witch(float x, float y);
	~Witch();
	//const std::string path = "Models/witch/witch-toon.obj";
};

#endif