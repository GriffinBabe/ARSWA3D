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
			case GLFW_KEY_UP:	std::cout << "key up called" << std::endl;
								break;
		}
	}

}
