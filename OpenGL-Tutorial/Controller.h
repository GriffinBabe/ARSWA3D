#pragma once

#include "Window.h"

class Controller
{
public:
	Controller(Window* w);

	~Controller();
	void key_callback(GLFWwindow* glwindow, int key, int scancode, int action, int mods);

private:
	Window* window;
};

