#include "Entity.h"

Model * Entity::getModel() const
{
	return this->model;
}

DecorativeEntity::DecorativeEntity(float x, float y, Model * model)
{
	Entity::x = x;
	Entity::y = y;
	Entity::model = model;
}
