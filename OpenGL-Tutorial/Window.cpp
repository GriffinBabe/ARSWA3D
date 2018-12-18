#include "Window.h"
#include "Controller.h"
#include <iostream>

unsigned int WIDTH = 600, HEIGHT = 600;

const char *vertexShaderSource = 
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0"; 

const char *fragmentShaderSource = 
	"#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";

Window::Window()
{
	std::cout << "Window called" << std::endl;
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
	this->init_shaders();

	float vertices[] = {
	 0.5f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f
	};
	unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
	};
	this->triangle = new Triangle(12, 6, vertices, indices);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //  Wireframe mode

}

Window::~Window() {
	glfwTerminate();
	// Closes all gl components after the end of the game_loop
	delete this->triangle;
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
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); // Whenever we call glClear and clear the color buffer, the entire color buffer will be filled with the color as configured by glClearColor

		// We specifies wich Shader we use to render our triangle
		glUseProgram(shaderProgram); // We are using the shaders we build previously
		glBindVertexArray(*this->triangle->getVAO()); // We bind those vertex we want to draw
		// Only if we are not using EBO: glDrawArrays(GL_TRIANGLES, 0, 3);	// 1st arg: primitive type we want to draw
																			// 2nd arg: starting index for drawing
																			// 3rd arg: how many vertices we want to draw

		glDrawElements(GL_TRIANGLES, this->triangle->get_indices_size(), GL_UNSIGNED_INT, 0);	// 1st arg: primite type we want to draw
																// 2nd arg: 6 indices so 6 vertices to draw
																// 3rd arg: type of indicies (unsigned int)
																// 4th arg: EBO offset (so we start at the first element of the indicies array in this case)
																// It takes the EBO bound to the VAO, and the VAO is currently bound with glBindVertexArray( vao );

		glfwSwapBuffers(window); // Swamp the buffer to the window, there are two buffers: one that is rendering and one from the previous frame that already rendered, 
								 // we want to show the already rendered one to avoid flickering!
		glfwPollEvents(); // Checks if any events are trigerred
	}
}

void Window::init_shaders()
{
	// Initializes the shaders

	int succ;
	char infoLog[512];

	vertexShader = glCreateShader(GL_VERTEX_SHADER); // Creates a shader and returns the id of the shader. Since we're creating a vertex shader we pass in GL_VERTEX_SHADER.
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Takes the source code
	glCompileShader(vertexShader); // Compiles the shader with the id as vertexShader

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &succ); // Checks if the compilation SUCC'd
	if (!succ) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // We do the same for the fragment shader, wich gives the color of the pixels
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &succ); // Checks if the compilation SUCC'd
	if (!succ) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	shaderProgram = glCreateProgram(); // A shader program object is the final linked version of multiple shaders combined
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &succ);
	if (!succ) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Window::key_callback_thunk(GLFWwindow * glwindow, int key, int scancode, int action, int mods)
{
	auto self = static_cast<Controller*>(glfwGetWindowUserPointer(glwindow));
	self->key_callback(glwindow, key, scancode, action, mods);
}
