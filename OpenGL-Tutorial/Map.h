#ifndef MAP_H
#define MAP_H

#include "Entity.h"
#include "SolidEntity.h"
#include "ModelList.h"
#include <vector>

class Map
{
public:
	Map();
	~Map();

	const std::vector<Entity*>& getEntities() { return entities; }
	float boundary_left = -4.0f, boudary_right = 4.0f, boundary_top = 4.5f, boundary_bottom = 0.0f;

private:
	std::vector<Entity*> entities;


};

#endif