#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include "Observer.h"

class Entity;

class Model : public Observer {
public: 

	Model();

	/**
		Creates a model from loaded meshes.

		@param meshes, the preloaded list of meshes
	*/
	Model(std::vector<Mesh*> meshes);

	/**
		NB: x_off are the distance between the center of the mesh (ofter located at the center bottom) to
		what we might use as the center in the model.
	*/
	void setOffsets(float x, float y) { x_off = x; y_off = y; }
	float x_off = 0.0f; float y_off = 0.0f;


	/**
		Renders the model for each linked entity
		
		@param shader, the OpenGL shader we are using to render this model
		@param delta_time, the time passed since the last game loop
	*/
	void draw(Shader* shader, float delta_time);

	/**
		Observer/Observable pattern implementation on game Entities.
	*/
	void removeEntity(Entity* entity);
	void addEntity(Entity* entity);
	void onNotify(Entity& entitiy, EEvent event) override;

	std::vector<Mesh*>* getMeshes();

protected:
	std::vector<Mesh*> meshes;
	std::vector<Entity*> entities;

};

#endif