#include "Map.h"

Map::Map() : entities(std::vector<Entity*>())
{
	// We need to add map objects but we are going to let only one for this moment
	Entity* main_platform = new DecorativeEntity(0.0f, -0.15f);
	ModelList::platform->addEntity(main_platform);

	main_platform->z = 0.5f;
	main_platform->scaleX = 1.5f;
	main_platform->scaleY = 1.5f;
	entities.push_back(main_platform);
	
	SolidEntity* upper_platform = new SolidEntity(0.0f, 3.0f, 5.0f, 0.1f);
	ModelList::platform->addEntity(upper_platform);


	main_platform->z = 0.5f;
	main_platform->scaleX = 1.5f;
	main_platform->scaleY = 1.5f;
	entities.push_back(upper_platform);



	SolidEntity* platform_left = new SolidEntity(-2.0f, 1.5f, 2.75f, 0.1f);
	ModelList::platform->addEntity(platform_left);

	platform_left->z = 0.5f;
	platform_left->scaleX = 0.5f;
	entities.push_back(platform_left);

	SolidEntity* platform_right = new SolidEntity(2.0f, 1.5f, 2.75f, 0.1f);
	ModelList::platform->addEntity(platform_right);
	platform_right->z = 0.5f;
	platform_right->scaleX = 0.5f;
	entities.push_back(platform_right);

	Entity* back_wall = new DecorativeEntity(0.0f, 2.0f);
	ModelList::wall->addEntity(back_wall);
	back_wall->z = -1.0f;
	back_wall->scaleX = 4.0f;
	back_wall->scaleY = 4.0f;

	Entity* left_wall = new DecorativeEntity(-4.0f, 2.0f);
	ModelList::wall->addEntity(left_wall);

	left_wall->rotY = -90.0f;
	left_wall->z = -1.0f;
	left_wall->scaleX = 4.0f;
	left_wall->scaleY = 4.0f;
	entities.push_back(left_wall);

	Entity* right_wall = new DecorativeEntity(4.0f, 2.0f);
	ModelList::wall->addEntity(right_wall);

	right_wall->rotY = 90.0f;
	right_wall->z = -1.0f;
	right_wall->scaleX = 4.0f;
	right_wall->scaleY = 4.0f;
	entities.push_back(right_wall);

	Entity* roof = new DecorativeEntity(0.0f, 4.5f);
	roof->scaleX = 4.0f;
	roof->scaleY = 3.0f;
	roof->scaleZ = 4.0f;

	entities.push_back(roof);
}


Map::~Map()
{
	for (Entity* entity : entities) {
		// We still need to unatach the entities from the model and game etc!
		delete entity;
	}
}