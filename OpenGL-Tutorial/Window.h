#ifndef  WINDOW_H
#define WINDOW_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include <vector>

#include "Game.h"

class Controller;

class Window
{
public:
	Window();
	~Window();

	void set_game(Game* game);

	void set_callback(Controller* ctrl);
	void set_mouse_callback(Controller* ctrl);
	void game_loop();

	Camera* getCamera();

private:
	Game* game;

	GLFWwindow* window;
	Shader* shader;
	Camera* camera;

	std::vector<Model> models;

	bool game_set = false;
	bool kill_pill = false;
	bool print_fps = false;

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow* window);

	static void key_callback_thunk(GLFWwindow* glwindow, int key, int scancode, int action, int mods);
	static void mouse_callback_thunk(GLFWwindow* glwindow, double xpos, double ypos);

	std::string glsl_reader(std::string filePath);

};

#endif // ! WINDOW_H
