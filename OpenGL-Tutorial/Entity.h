#ifndef ENTITY_H
#define ENTITY_H


#include "Model.h"
class Entity
{
public:
	Entity(float x, float y, std::string path);
	~Entity();
	float x, y; // Those are game model coordinates (the game model is on a 2D space)

	Model* getModel() const;

private:
	Model* model;
};

#endif // !ENTITY_H
