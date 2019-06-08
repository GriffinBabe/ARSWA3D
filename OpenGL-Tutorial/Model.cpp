#include "Model.h"
#include "Entity.h"


Model::Model() : meshes(std::vector<Mesh>()), entities(std::vector<Entity*>())
{
}

Model::Model(std::vector<Mesh> meshes) : meshes(meshes), entities(std::vector<Entity*>())
{

}

void Model::draw(Shader * shader, float delta_time)
{
	for (Entity* entity : entities) {
		glm::mat4 model = glm::mat4(1.0f);
		if (entity != nullptr) {
			model = glm::translate(model, glm::vec3(entity->x - x_off, entity->y - y_off, entity->z));
			model = glm::rotate(model, glm::radians(entity->rotX), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(entity->rotY), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(entity->rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(entity->scaleX, entity->scaleY, entity->scaleZ));
		}
		else {
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		}
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		shader->setMatrix4f("model", model);
		for (unsigned int i = 0; i < meshes.size(); i++) {
			meshes[i].draw(shader);
		}
	}
}

void Model::removeEntity(Entity * entity)
{
	entity->removeObserver(this);
	int index = 0;
	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it, ++index) {
		if (*it == entity) {
			break;
		}
	}
	entities.erase(entities.begin() + index);
}

void Model::addEntity(Entity * entity)
{
	entity->addObserver(this);
	entities.push_back(entity);
}

void Model::onNotify(Entity& entitiy, EEvent event)
{
	switch (event) {

	}
}