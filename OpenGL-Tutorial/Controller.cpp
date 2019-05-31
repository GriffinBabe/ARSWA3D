#include "Controller.h"
#include "Command.h"


Controller::Controller(Window* w, Game* g)
{
	this->window = w;
	this->game = g;
	this->localCharacter = this->game->getLocalPlayer()->getCharacter();
}


Controller::~Controller()
{
}

void Controller::key_callback(GLFWwindow* glwindow, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_F:		
			this->window->getCamera()->switch_free();
			break;
		case GLFW_KEY_W:
			pressUp = true;
			if (!pressDown)
				game->addCommand(new JumpCommand(localCharacter));
			break;
		case GLFW_KEY_S:
			pressDown = true;
			checkDirections();
			break;
		case GLFW_KEY_A:
			pressLeft = true;
			checkDirections();
			break;
		case GLFW_KEY_D:		
			pressRight = true;
			checkDirections();
		case GLFW_KEY_UP:		
			this->window->getCamera()->set_camera_dz(-1);
			break;
		case GLFW_KEY_DOWN:		
			this->window->getCamera()->set_camera_dz(1);
			break;
		case GLFW_KEY_LEFT:		
			this->window->getCamera()->set_camera_dx(-1);
			break;
		case GLFW_KEY_RIGHT:	
			this->window->getCamera()->set_camera_dx(1);
			break;
		}
	}
	else if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_W:
			pressUp = false;
			break;
		case GLFW_KEY_S:
			pressDown = false;
			checkDirections();
			break;
		case GLFW_KEY_A:
			pressLeft = false;
			checkDirections();
			break;
		case GLFW_KEY_D:		
			pressRight = false;
			checkDirections();
			break;
		case GLFW_KEY_UP:		
			this->window->getCamera()->set_camera_dz(0);
			break;
		case GLFW_KEY_DOWN:		
			this->window->getCamera()->set_camera_dz(0);
			break;
		case GLFW_KEY_LEFT:		
			this->window->getCamera()->set_camera_dx(0);
			break;
		case GLFW_KEY_RIGHT:	
			this->window->getCamera()->set_camera_dx(0);
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

void Controller::checkDirections()
{
	if (!pressDown) {
		if (!pressLeft && !pressRight) {
			game->addCommand(new DirectionCommand(this->localCharacter, 0));
			return;
		}
		else if (pressLeft && pressRight) {
			game->addCommand(new DirectionCommand(this->localCharacter, 0));
			return;
		}
		else if (pressLeft && !pressRight) {
			game->addCommand(new DirectionCommand(this->localCharacter, -1));
			return;
		}
		else if (pressRight && !pressLeft) {
			game->addCommand(new DirectionCommand(this->localCharacter, 1));
			return;
		}
		else {
			game->addCommand(new DirectionCommand(this->localCharacter, 0));
			return;
		}
	}
	else {
		game->addCommand(new DirectionCommand(this->localCharacter, 0));
		return;
	}
}
