#include "Controller.h"



Controller::Controller(Window* w)
{
	this->window = w;
}


Controller::~Controller()
{
}

void Controller::key_callback(GLFWwindow* glwindow, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_UP:		this->window->getCamera()->set_camera_dz(-1);
			break;
		case GLFW_KEY_DOWN:		this->window->getCamera()->set_camera_dz(1);
			break;
		case GLFW_KEY_LEFT:		this->window->getCamera()->set_camera_dx(-1);
			break;
		case GLFW_KEY_RIGHT:	this->window->getCamera()->set_camera_dx(1);
			break;
		}
	}
	else if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_UP:		this->window->getCamera()->set_camera_dz(0);
			break;
		case GLFW_KEY_DOWN:		this->window->getCamera()->set_camera_dz(0);
			break;
		case GLFW_KEY_LEFT:		this->window->getCamera()->set_camera_dx(0);
			break;
		case GLFW_KEY_RIGHT:	this->window->getCamera()->set_camera_dx(0);
			break;

		}
	}

}

void Controller::mouse_callback(GLFWwindow * glwindow, double xpos, double ypos)
{
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;

	xoffset *= mouse_sensitivity;
	yoffset *= mouse_sensitivity;	

	this->window->getCamera()->change_yaw_offset(xoffset);
	this->window->getCamera()->change_pitch_offset(yoffset);
}
