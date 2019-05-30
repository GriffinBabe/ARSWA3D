#ifndef  SOLIDENTITY_H
#define SOLIDENTITY_H

#include "Entity.h"

/*
*	Same as an Entity, but has collision propreties.
*/

class SolidEntity : public Entity
{
public:

	SolidEntity(float x, float y, Model * model);

	// Initialised like this by platforms
	SolidEntity(float x, float y, float x_off, float y_off, float width, float height, Model* model);
	~SolidEntity();

	/**
		Checks if the given solidentity collides with this one.
		@param entity, the moving entity we want to check collision
	*/
	bool check_collision(SolidEntity* entity);


	float width = 0; float height = 0;
	float x_off = 0; float y_off = 0; // The offset compared to the render point
};
#endif // ! SOLIDENTITY_H

