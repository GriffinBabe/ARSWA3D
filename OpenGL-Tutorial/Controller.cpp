#include "Controller.h"



Controller::Controller(Window* w, Game* g)
{
	this->window = w;
	this->game = g;
}


Controller::~Controller()
{
}

void Controller::key_callback(GLFWwindow* glwindow, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_F:		this->window->getCamera()->switch_free();
			break;
		case GLFW_KEY_W:		this->game->getLocalPlayer()->getCharacter()->set_press_up(true);
			break;
		case GLFW_KEY_S:		//
			break;
		case GLFW_KEY_A:		this->game->getLocalPlayer()->getCharacter()->set_press_left(true);
			break;
		case GLFW_KEY_D:		this->game->getLocalPlayer()->getCharacter()->set_press_right(true);
			break;
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
		case GLFW_KEY_W:		this->game->getLocalPlayer()->getCharacter()->set_press_up(false);
			break;
		case GLFW_KEY_S:
			break;
		case GLFW_KEY_A:		this->game->getLocalPlayer()->getCharacter()->set_press_left(false);
			break;
		case GLFW_KEY_D:		this->game->getLocalPlayer()->getCharacter()->set_press_right(false);
			break;
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
