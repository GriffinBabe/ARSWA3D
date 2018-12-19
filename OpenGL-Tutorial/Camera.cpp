#include "Camera.h"


Camera::Camera(Shader * sha) : view(glm::mat4()), projection(glm::mat4()), position(glm::vec3()), direction(glm::vec3())
{
	this->shader = sha;
	position = glm::vec3(0.0f, 0.0f, -3.0f);
	view = glm::translate(view, position);
	projection = glm::perspective(glm::radians(45.0f), 600.0f/600.0f, 0.1f, 100.0f);
}

Camera::~Camera()
{
}

void Camera::set_matrices()
{
	this->shader->setMatrix4f("view", view);
	this->shader->setMatrix4f("projection", projection);
}

void Camera::set_target(glm::vec3 tar)
{
	direction = glm::normalize(position - tar);
}

