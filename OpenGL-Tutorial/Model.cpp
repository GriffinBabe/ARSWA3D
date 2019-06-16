#include "Model.h"
#include "Entity.h"


Model::Model() : meshes(std::vector<Mesh*>()), instances(std::vector<ModelInstance*>()), observers(std::vector<Entity*>())
{
	rigged = false;
}

Model::Model(std::vector<Mesh*> meshes,bool rigged) : meshes(meshes), instances(std::vector<ModelInstance*>()), observers(std::vector<Entity*>()), rigged(rigged)
{

}

void Model::draw(Shader * shader, float delta_time)
{
	if (rigged) {
		std::cout << std::endl;
	}
	for (ModelInstance* instance : instances) {
		instance->draw(shader, delta_time);
	}
}

void Model::removeInstance(Entity * entity)
{
	int index = 0;
	for (std::vector<ModelInstance*>::iterator it = instances.begin(); it != instances.end(); ++it, ++index) {
		if ((**it).getEntity() == entity) {
			break;
		}
	}
	entity->removeObserver(instances[index]);
	instances.erase(instances.begin() + index);
}

void Model::addInstance(Entity * entity)
{
	ModelInstance* instance;
	if (rigged) {
		instance = new AModelInstance(dynamic_cast<RiggedMesh*>(meshes[0]), entity, x_off, y_off);
	}
	else {
		instance = new ModelInstance(meshes[0], entity, x_off, y_off);
	}
	instances.push_back(instance);
	entity->addObserver(instances.back());
}

void Model::addObserver(Entity * entity)
{
	entity->addObserver(this);
	observers.push_back(entity);
}

void Model::removeObserver(Entity * entity)
{
	int index = 0;
	for (std::vector<Entity*>::iterator it = observers.begin(); it != observers.end(); ++it, ++index) {
		if ((*it) == entity) {
			break;
		}
	}
	entity->removeObserver(this);
	observers.erase(observers.begin() + index);
}

void Model::onNotify(Entity& entitiy, EEvent event)
{
	switch (event) {

	}
}

std::vector<Mesh*>* Model::getMeshes()
{
	return &meshes;
}
