#include "AnimatedModel.h"
#include <stdexcept>
#include <map>

AnimatedModel::AnimatedModel(std::string path, float x_off, float y_off)
	: Model(path,x_off,y_off), meshes(std::vector<AnimatedMesh>()), boneMap(std::map<std::string,unsigned int>())
{
	loadModel(path);
}

AnimatedModel::AnimatedModel(std::vector<AnimatedMesh> meshes) : meshes(meshes)
{
}

AnimatedModel::AnimatedModel()
{
}


AnimatedModel::~AnimatedModel()
{
}

void AnimatedModel::draw(Shader * shader, Entity * entity)
{
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

