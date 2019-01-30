#ifndef ENTITY_H
#define ENTITY_H


#include "Model.h"
class Entity
{
public:
	Entity(float x, float y, Model* model);
	~Entity();

	float x = 0, y = 0; // Those are game model coordinates (the game model is on a 2D space)
	float z = 0; // for decorative entities
	float width = 0; float height = 0;
	float rotX=0, rotY=0, rotZ=0; // By default they are null
	float scaleX = 1.0f; float scaleY = 1.0f; float scaleZ = 1.0f;

	Model* getModel() const;

	bool collidable = false;

protected:
	Model* model;
};

#endif // !ENTITY_H
