#include "Window.h"
#include "Controller.h"
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

unsigned int WIDTH = 600, HEIGHT = 600;

Window::Window() : models(std::vector<Model>())
{
	/*
	 * Initialises the Opengl and gives the version 3.3
	*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
	#endif

	/*
	Initializes the window and checks if it has been build correctly
	*/
	this->window = glfwCreateWindow(WIDTH, HEIGHT, "ARSWA Rem.", NULL, NULL);
	if (this->window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	/*
	*	Calls framebuffer_size_callback everytime the window gets resized
	*/
	glfwMakeContextCurrent(this->window);
	//glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}

	models.push_back(Model("Models/cube/cube.obj"));

	// Initializes the shaders and installs them
	this->shader = new Shader("GLSL/multiple_vertex_source.c", "GLSL/model_loading.c");
	this->camera = new Camera(this->shader);
	glEnable(GL_DEPTH_TEST); // opengl's Z buffer used so things that are behind others aren't rendered
}

Window::~Window() {
	glfwTerminate();
	// Closes all gl components after the end of the game_loop
	delete this->shader;
}

void Window::set_callback(Controller* ctrl)
{
	glfwSetWindowUserPointer(this->window, ctrl);
	glfwSetKeyCallback(this->window, key_callback_thunk);
}

void Window::set_mouse_callback(Controller * ctrl)
{
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowUserPointer(this->window, ctrl);
	glfwSetCursorPosCallback(this->window, mouse_callback_thunk);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void Window::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void Window::game_loop() {
	float last_time = glfwGetTime();
	unsigned int nbFrames = 0;
	while (!glfwWindowShouldClose(window) || kill_pill) { // Checks if the window has received the instruction to close or another thread from this program activated the kill_pill
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - last_time >= 1.0) { // If last prinf() was more than 1 sec ago
			if (print_fps) {
				printf("%f FPS\n", double(nbFrames));
			}
			nbFrames = 0;
			last_time += 1.0;
		}

		processInput(window);

		// ... Redering commands here ... //
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.19f, 0.54f, 0.62f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT); // Whenever we call glClear and clear the color buffer, the entire color buffer will be filled with the color as configured by glClearColor


		//float time = glfwGetTime();
		//int vertexColorLocation = glGetUniformLocation(this->shader->program_ID, "ourColor"); // Gets the ID of the uniform variable that is our coloration in this case
		//glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 1.0f); // With our ID we get the uniform variable, and we change the values
		this->shader->use();
		this->camera->set_matrices();

		for (Model md : models) {
			// We specifies wich Shader we use to render our triangle
			md.draw(this->shader);
		}

		glfwSwapBuffers(window); // Swamp the buffer to the window, there are two buffers: one that is rendering and one from the previous frame that already rendered, 
								 // we want to show the already rendered one to avoid flickering!
		glfwPollEvents(); // Checks if any events are trigerred
	}
}

Camera * Window::getCamera()
{
	return this->camera;
}

void Window::key_callback_thunk(GLFWwindow * glwindow, int key, int scancode, int action, int mods)
{
	auto self = static_cast<Controller*>(glfwGetWindowUserPointer(glwindow));
	self->key_callback(glwindow, key, scancode, action, mods);
}

void Window::mouse_callback_thunk(GLFWwindow * glwindow, double xpos, double ypos)
{
	auto self = static_cast<Controller*>(glfwGetWindowUserPointer(glwindow));
	self->mouse_callback(glwindow, xpos, ypos);
}

std::string Window::glsl_reader(std::string filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}