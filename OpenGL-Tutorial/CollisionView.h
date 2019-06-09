#ifndef  COLLISIONVIEW_H
#define COLLISIONVIEW_H

#include "Shader.h"
#include "SolidEntity.h"

// Changing code test
class CollisionView
{
public:
	CollisionView();
	~CollisionView();

	void draw(Shader* shader, SolidEntity* entity);

private:
	
	unsigned int VAO, VBO, EBO;

};

#endif // ! COLLISIONVIEW_H
