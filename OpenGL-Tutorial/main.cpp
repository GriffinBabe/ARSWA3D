#include <iostream>
#include "Window.h"
#include "Controller.h"

int main()
{
	Window* window = new Window();
	Controller* controller = new Controller(window);
	window->set_callback(controller);
	window->set_mouse_callback(controller);
	window->game_loop();
	return 0;
}