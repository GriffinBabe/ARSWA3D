#ifndef  MODELINSTANCE_H
#define MODELINSTANCE_H

#include "Mesh.h"
#include "Observer.h"
#include "Shader.h"
#include "Entity.h"
#include "Mob.h"

class ModelInstance : public Observer
{
public:
	ModelInstance(Mesh* mesh, Entity* entity, float x_off, float y_off);
	~ModelInstance();
	
	Entity* getEntity() { return entity; }

	virtual void draw(Shader* shader, float delta_time);

protected:

	/**
		Handle events from entity
	*/
	void onNotify(Entity* entity, EEvent event);


	Entity* entity;

	/**
		Mesh from the entity we are observing
	*/
	Mesh* mesh;

	float x_off, y_off;
};


class AModelInstance : public ModelInstance
/**
	Same as ModelInstance but we know the given mesh is a RiggedMesh
*/
{
public:
	AModelInstance(RiggedMesh* mesh, Entity* Entity, float x_off, float y_off);
	~AModelInstance() {};

	void draw(Shader* Shader, float delta_time) override;

private:
	Animator animator;

	void onNotify(Entity* entity, EEvent event) override;
};

#endif //  MODELINSTANCE_H