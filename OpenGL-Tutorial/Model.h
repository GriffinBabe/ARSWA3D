#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include "Observer.h"
#include "ModelInstance.h"

class Entity;

class Model : public Observer {
public: 

	Model();

	/**
		Creates a model from loaded meshes.

		@param meshes, the preloaded list of meshes
	*/
	Model(std::vector<Mesh*> meshes, bool rigged=false);

	void setRigged(bool r) { rigged = r; }

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
		Observer/Observable pattern implementation for Instances.
		An instance is an Entity observer. But the Model can also be an Enity observer.
		Exemple a character will be an instance. An arrow an instance. But the manager of the arrow will
		be linked to the Model and not the arrow
	*/
	void removeInstance(Entity* entity);
	void addInstance(Entity* entity);

	void addObserver(Entity* entity);
	void removeObserver(Entity* entity);

	void onNotify(Entity& entitiy, EEvent event) override;

	std::vector<Mesh*>* getMeshes();

protected:
	std::vector<Mesh*> meshes;
	std::vector<Entity*> observers;
	std::vector<ModelInstance*> instances;
	std::vector<Animation> animations;

	bool rigged = false;

};

#endif