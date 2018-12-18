#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Triangle.h"
#include "Shader.h"

class Controller;

class Window
{
public:
	Window();
	~Window();

	void set_callback(Controller* ctrl);
	void game_loop();

	Triangle* getTriangle();

private:
	GLFWwindow* window;
	Shader* shader;

	Triangle* triangle;

	bool kill_pill = false;

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow* window);

	static void key_callback_thunk(GLFWwindow* glwindow, int key, int scancode, int action, int mods);

	std::string glsl_reader(std::string filePath);

};

