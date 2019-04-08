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

bool SolidEntity::check_collision(SolidEntity * entity1, SolidEntity * entity2)
{
	if (entity1->x + entity1->x_off + entity1->width / 2 > entity2->x + entity2->x_off - entity2->width / 2 &&
		entity1->x + entity1->x_off - entity1->width / 2 < entity2->x + entity2->x_off + entity2->width / 2 && 
		entity1->y + entity1->y_off < entity2->y + entity2->y_off + entity2->height &&
		entity1->y + entity1->y_off + entity1->height > entity2->y + entity2->y_off) {
		return true;
	}
	return false;
}
