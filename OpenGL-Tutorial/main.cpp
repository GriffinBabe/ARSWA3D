#include <iostream>
#include "Window.h"
#include "Controller.h"

int main()
{
	Window* window = new Window();
	Game* game = new Game();
	window->set_game(game);
	Controller* controller = new Controller(window, game);
	window->set_callback(controller);
	window->set_mouse_callback(controller);
	window->game_loop();
	return 0;
}