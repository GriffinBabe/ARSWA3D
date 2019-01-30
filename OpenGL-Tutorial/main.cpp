#include <iostream>
#include "Window.h"
#include "Controller.h"

int main()
{
	Window* window = new Window();

	// By default ModelList Models pointers are nullptr as we want to avoid stbi_load Access read violations
	ModelList::Init(); // calls constructor is a static way, because by default definitions are nullptr

	Game* game = new Game();
	window->set_game(game);
	Controller* controller = new Controller(window, game);
	window->set_callback(controller);
	window->set_mouse_callback(controller);
	window->game_loop();

	ModelList::clear();
	delete game; delete controller; delete window;
	return 0;
}