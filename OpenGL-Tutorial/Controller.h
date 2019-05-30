#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Window.h"
#include "Game.h"

class Controller
{
public:
	Controller(Window* w, Game* g);

	~Controller();
	void key_callback(GLFWwindow* glwindow, int key, int scancode, int action, int mods);
	void mouse_callback(GLFWwindow* glwindow, double xpos, double ypos);

private:
	Game* game;
	Character* localCharacter;
	Window* window;
	float lastX = 400, lastY = 300;
	float mouse_sensitivity = 0.1f;

	bool pressUp = false;
	bool pressDown = false;
	bool pressLeft = false;
	bool pressRight = false;
};

#endif // CONTROLLER_H

