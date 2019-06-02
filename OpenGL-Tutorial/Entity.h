#ifndef ENTITY_H
#define ENTITY_H

#include "Model.h"

/**
	Base class for all game entities, ranging from Characters to Projectiles,
	NPCs to Decorations of the map.

	The entity contains position, size, rotation of the model in world
	coordinates. And are used to render as to game logic.

	Also, an entity always has a model to render.

	@Author: Darius Couchard
*/

struct Position {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};

class Entity
{
public:
	Entity() {};
	virtual ~Entity() {};

	float x = 0, y = 0; // Those are game model coordinates (the game model is on a 2D space)
	float z = 0; // for decorative entities
	//float width = 0; float height = 0;
	float rotX=0, rotY=0, rotZ=0; // By default they are null
	float scaleX = 1.0f; float scaleY = 1.0f; float scaleZ = 1.0f;

	Model* getModel() const;

	/**
		By default is not collidable, in SolidEntity by default it is collidable,
		but stuff like projectiles can not be collidable. Even if they can collide on other entities.
	*/
	bool collidable = false;

protected:
	Model* model;
	// Info, subclass sandbox can help decoupling. Ex: we can put static Game* game; and access the game from every entity
};

/**
	Simple trick so we can instatiate Entity (which is an abstract class).
	This class is generally used on decorative models that don't have impact on gameplay
	@Author Darius Couchard
*/

class DecorativeEntity : public Entity
{
public:
	DecorativeEntity(float x, float y, Model* model);

	void dummyPolymorphic() {}
};

#endif // !ENTITY_H
