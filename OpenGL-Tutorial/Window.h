#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Triangle.h"

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
	unsigned int vertexShader = 0;
	unsigned int fragmentShader = 0;
	unsigned int shaderProgram = 0;

	Triangle* triangle;

	bool kill_pill = false;

	void init_shaders();
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow* window);

	static void key_callback_thunk(GLFWwindow* glwindow, int key, int scancode, int action, int mods);

};

