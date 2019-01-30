#ifndef  SOLIDENTITY_H
#define SOLIDENTITY_H

#include "Entity.h"

class SolidEntity : public Entity
{
public:
	SolidEntity(float x, float y, Model* model);
	SolidEntity(float x, float y, float x_off, float y_off,float width, float height, Model* model);
	~SolidEntity();

	float width = 0; float height = 0;
	float x_off = 0; float y_off = 0; // The offset compared to the render point

};
#endif // ! SOLIDENTITY_H

