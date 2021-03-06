#include "ModelInstance.h"

ModelInstance::ModelInstance(Mesh * mesh, Entity* entity, float x_off, float y_off) : x_off(x_off), y_off(y_off)
{
	this->mesh = mesh;
	this->entity = entity;
}

ModelInstance::~ModelInstance()
{
	// Doesn't delete mesh as it's kept by the model
}

void ModelInstance::draw(Shader * shader, float delta_time)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(entity->x - x_off, entity->y - y_off, entity->z));
	model = glm::rotate(model, glm::radians(entity->rotX), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(entity->rotY), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(entity->rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(entity->scaleX, entity->scaleY, entity->scaleZ));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	shader->setMatrix4f("model", model);
	mesh->draw(shader);
}

void ModelInstance::onNotify(Entity* entity, EEvent event)
{
	std::cout << "On notify called!" << std::endl;
	// TODO Define the behaviour
}

AModelInstance::AModelInstance(RiggedMesh * mesh, Entity * entity, float x_off, float y_off) : ModelInstance(mesh, entity, x_off, y_off), animator(Animator(mesh))
{
	// Copies the bones positions
	
}

void AModelInstance::draw(Shader * shader, float delta_time)
{
	// Same as draw but must apply animations first
	animator.update(delta_time);
	ModelInstance::draw(shader, delta_time);
}

void AModelInstance::onNotify(Entity* entity, EEvent event)
{
	std::cout << "On notify called in Animated model instace" << std::endl;
	RiggedMesh* rm = dynamic_cast<RiggedMesh*>(mesh);
	Mob* mob = dynamic_cast<Mob*>(entity);

	switch (event) {

	case WALK:
		if (mob->getDirection() != 0)
			animator.doAnimation("Stick|Walk");
		else
			animator.doAnimation(nullptr);
		break;
	}
}
