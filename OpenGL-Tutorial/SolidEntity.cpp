#include "SolidEntity.h"


SolidEntity::SolidEntity(float x, float y, Model * model) : Entity(x,y,model)
{
	collidable = true;
}

SolidEntity::SolidEntity(float x, float y, float width, float height, Model* model)
	: Entity(x, y, model), width(width), height(height)
{
	collidable = true;
}

SolidEntity::~SolidEntity()
{
}

bool SolidEntity::check_collision(SolidEntity * entity)
{
	std::cout << "Collision!" << std::endl;
	// TODO: Define collisions here
	if (x + (width / 2) > entity->x - entity->width / 2 && x - (width / 2) < entity->x + entity->width / 2
		&& y + (height / 2) > entity->y + entity->height / 2 && y - height / 2 < entity->y + entity->height / 2)
		return true;
	return false;
}
