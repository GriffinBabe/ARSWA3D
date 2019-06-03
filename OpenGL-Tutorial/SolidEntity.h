#ifndef  SOLIDENTITY_H
#define SOLIDENTITY_H

#include "Entity.h"

/*
*	Same as an Entity, but has collision propreties.
*/

class SolidEntity : public Entity
{
public:

	SolidEntity(float x, float y);

	// Initialised like this by platforms
	SolidEntity(float x, float y, float width, float height);
	~SolidEntity();

	/**
		Checks if the given solidentity collides with this one.
		@param entity, the moving entity we want to check collision
	*/
	bool check_collision(SolidEntity* entity);

	float width = 0; float height = 0;
};
#endif // ! SOLIDENTITY_H

