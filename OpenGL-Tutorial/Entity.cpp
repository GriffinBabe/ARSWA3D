#include "Entity.h"


Entity::Entity(float x, float y,Model* model) : x(x), y(y)
{
	this->model = model;
}


Entity::~Entity()
{
}

Model * Entity::getModel() const
{
	return this->model;
}
