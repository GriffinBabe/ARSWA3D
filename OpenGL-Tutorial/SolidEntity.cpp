#include "SolidEntity.h"


SolidEntity::SolidEntity(float x, float y, Model * model) : Entity(x,y,model)
{
	collidable = true;
}

SolidEntity::SolidEntity(float x, float y, float x_off, float y_off, float width, float height, Model* model)
	: Entity(x, y, model), width(width), height(height), x_off(x_off), y_off(y_off)
{
	collidable = true;
}

SolidEntity::~SolidEntity()
{
}

bool SolidEntity::check_collision(SolidEntity * entity)
{
	// TODO: Define collisions here
	return false;
}
