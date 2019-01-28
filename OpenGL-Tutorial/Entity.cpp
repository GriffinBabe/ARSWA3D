#include "Entity.h"



Entity::Entity(float x, float y, std::string path) : x(x), y(y)
{
	this->model = new Model(path, this);

}


Entity::~Entity()
{
}

Model * Entity::getModel() const
{
	return this->model;
}
