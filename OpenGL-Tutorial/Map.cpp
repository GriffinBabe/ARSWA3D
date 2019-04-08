#include "Map.h"

Map::Map()
{
	this->collision_entities = new std::vector<SolidEntity*>();
	this->decorative_entities = new std::vector<Entity*>();

	// We need to add map objects but we are going to let only one for this moment
	Entity* main_platform = new Entity(0.0f, -0.06f, ModelList::platform);
	main_platform->z = 0.5f;
	main_platform->scaleX = 1.5f;
	main_platform->scaleY = 1.5f;
	this->decorative_entities->push_back(main_platform);
	
	SolidEntity* upper_platform = new SolidEntity(0.0f, 2.8f, 0.0f, 0.05f, 5.0f, 0.1f, ModelList::platform);
	main_platform->z = 0.5f;
	main_platform->scaleX = 1.5f;
	main_platform->scaleY = 1.5f;
	this->collision_entities->push_back(upper_platform);


	SolidEntity* platform_left = new SolidEntity(-2.0f, 1.5f, 0.0f, 0.05f, 2.75f, 0.1f, ModelList::platform);
	platform_left->z = 0.5f;
	platform_left->scaleX = 0.5f;
	this->collision_entities->push_back(platform_left);

	SolidEntity* platform_right = new SolidEntity(2.0f, 1.5f, 0.0f, 0.05f, 2.75f, 0.1f, ModelList::platform);
	platform_right->z = 0.5f;
	platform_right->scaleX = 0.5f;
	this->collision_entities->push_back(platform_right);

	Entity* back_wall = new Entity(0.0f, 2.0f, ModelList::wall);
	back_wall->z = -1.0f;
	back_wall->scaleX = 4.0f;
	back_wall->scaleY = 4.0f;
	this->decorative_entities->push_back(back_wall);

	Entity* left_wall = new Entity(-4.0f, 2.0f, ModelList::wall);
	left_wall->rotY = -90.0f;
	left_wall->z = -1.0f;
	left_wall->scaleX = 4.0f;
	left_wall->scaleY = 4.0f;
	this->decorative_entities->push_back(left_wall);

	Entity* right_wall = new Entity(4.0f, 2.0f, ModelList::wall);
	right_wall->rotY = 90.0f;
	right_wall->z = -1.0f;
	right_wall->scaleX = 4.0f;
	right_wall->scaleY = 4.0f;
	this->decorative_entities->push_back(right_wall);

	Entity* roof = new Entity(0.0f, 4.5f, ModelList::roof);
	roof->scaleX = 4.0f;
	roof->scaleY = 3.0f;
	roof->scaleZ = 4.0f;
	this->decorative_entities->push_back(roof);
}


Map::~Map()
{
	for (Entity* en : *this->collision_entities) {
		delete en;
	}
	for (Entity* en : *this->decorative_entities) {
		delete en;
	}
}

std::vector<SolidEntity*>* Map::get_collision_entities()
{
	return collision_entities;
}

std::vector<Entity*>* Map::get_decorative_entities()
{
	return decorative_entities;
}
