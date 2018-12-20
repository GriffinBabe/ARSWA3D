#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Triangle.h"
#include "Shader.h"
#include "Camera.h"
#include <vector>

class Controller;

class Window
{
public:
	Window();
	~Window();

	void set_callback(Controller* ctrl);
	void set_mouse_callback(Controller* ctrl);
	void game_loop();

	Camera* getCamera();

private:
	GLFWwindow* window;
	Shader* shader;
	Camera* camera;

	std::vector<Model*>* models;

	bool kill_pill = false;
	bool print_fps = false;

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow* window);

	static void key_callback_thunk(GLFWwindow* glwindow, int key, int scancode, int action, int mods);
	static void mouse_callback_thunk(GLFWwindow* glwindow, double xpos, double ypos);

	std::string glsl_reader(std::string filePath);

};

