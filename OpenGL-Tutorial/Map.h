#ifndef MAP_H
#define MAP_H

#include "Entity.h"
#include <vector>

class Map
{
public:
	Map();
	~Map();

	std::vector<Entity*>* get_collision_entities();
	std::vector<Entity*>* get_decorative_entities();

private:
	std::vector<Entity*>* collision_entities;
	std::vector<Entity*>* decorative_entities;

};

#endif