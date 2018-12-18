#include "Window.h"
#include "Controller.h"
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

unsigned int WIDTH = 600, HEIGHT = 600;

Window::Window()
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
	this->window = glfwCreateWindow(WIDTH, HEIGHT, "GriffinBabe is learning OpenGL", NULL, NULL);
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

	// Initializes the shaders and installs them
	this->shader = new Shader("GLSL/tex_vertex_source1.c", "GLSL/tex_fragment_source1.c");

	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};
	unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
	};

	this->triangle = new Triangle(18, 3, vertices, indices);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //  Wireframe mode

}

Window::~Window() {
	glfwTerminate();
	// Closes all gl components after the end of the game_loop
	delete this->triangle;
	delete this->shader;
}

void Window::set_callback(Controller* ctrl)
{
	glfwSetWindowUserPointer(this->window, ctrl);
	glfwSetKeyCallback(this->window, key_callback_thunk);
}

Triangle * Window::getTriangle()
{
	return triangle;
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
	while (!glfwWindowShouldClose(window) || kill_pill) { // Checks if the window has received the instruction to close or another thread from this program activated the kill_pill
		processInput(window);

		// ... Redering commands here ... //
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT); // Whenever we call glClear and clear the color buffer, the entire color buffer will be filled with the color as configured by glClearColor

		// We specifies wich Shader we use to render our triangle
		this->shader->use();

		float time = glfwGetTime();

		//int vertexColorLocation = glGetUniformLocation(this->shader->program_ID, "ourColor"); // Gets the ID of the uniform variable that is our coloration in this case
		//glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 1.0f); // With our ID we get the uniform variable, and we change the values

		this->triangle->render();

		glfwSwapBuffers(window); // Swamp the buffer to the window, there are two buffers: one that is rendering and one from the previous frame that already rendered, 
								 // we want to show the already rendered one to avoid flickering!
		glfwPollEvents(); // Checks if any events are trigerred
	}
}

void Window::key_callback_thunk(GLFWwindow * glwindow, int key, int scancode, int action, int mods)
{
	auto self = static_cast<Controller*>(glfwGetWindowUserPointer(glwindow));
	self->key_callback(glwindow, key, scancode, action, mods);
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