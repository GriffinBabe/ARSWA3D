#pragma once

#include "Window.h"

class Controller
{
public:
	Controller(Window* w);

	~Controller();
	void key_callback(GLFWwindow* glwindow, int key, int scancode, int action, int mods);
	void mouse_callback(GLFWwindow* glwindow, double xpos, double ypos);

private:
	Window* window;
	float lastX = 400, lastY = 300;
	float mouse_sensitivity = 0.1f;
};

