#include "Camera.h"


Camera::Camera(Shader * sha) :
	view(glm::mat4())
{
	this->shader = sha;
	projection = glm::perspective(glm::radians(45.0f), 600.0f/600.0f, 0.1f, 100.0f);
	worldUp		= glm::vec3(0.0f, 1.0f, 0.0f);
	position	= glm::vec3(0.0f, 0.0f, 0.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp	= glm::vec3(0.0f, 1.0f, 3.0f);
}

Camera::~Camera()
{
}

void Camera::set_matrices() // called on each render loop
{
	float current_frame = glfwGetTime();
	delta_time = current_frame - last_frame;
	last_frame = current_frame;

	position -= cameraFront * dz * delta_time;
	position += cameraRight * dx * delta_time;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
	cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));

	view = glm::lookAt(position, position + cameraFront, cameraUp);
	this->shader->setMatrix4f("view", view);
	this->shader->setMatrix4f("projection", projection);
}

// direction is -1, 1, or 0
void Camera::set_camera_dx(int direction)
{
	dx = camera_speed * direction;
}

void Camera::set_camera_dz(int direction)
{
	dz = camera_speed * direction;
}

void Camera::change_yaw_offset(float dy)
{
	yaw += dy;
}

void Camera::change_pitch_offset(float dp)
{
	pitch += dp;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
}

void Camera::set_sprint(bool sprint)
{
	if (sprint) {
		camera_speed = 10.0f;
	}
	else {
		camera_speed = 3.0f;
	}
}

