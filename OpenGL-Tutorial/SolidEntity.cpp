#include "SolidEntity.h"


SolidEntity::SolidEntity(float x, float y, Model * model)
{
	Entity::x = x;
	Entity::y = y;
	Entity::model = model;
	collidable = true;
}

SolidEntity::SolidEntity(float x, float y, float width, float height, Model* model) : width(width), height(height)
{
	Entity::x = x;
	Entity::y = y;
	Entity::model = model;
	collidable = true;
}

SolidEntity::~SolidEntity()
{
}

bool SolidEntity::check_collision(SolidEntity * entity)
{
	// TODO: Define collisions here
	if (x + (width / 2) > entity->x - entity->width / 2 && x - (width / 2) < entity->x + entity->width / 2
		&& y + (height / 2) > entity->y - entity->height / 2 && y - height / 2 < entity->y + entity->height / 2) {
		return true;
	}
	return false;
}