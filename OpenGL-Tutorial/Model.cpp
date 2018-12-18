#include "Model.h"
#include <glad/glad.h>


Model::Model(int vertices_size, int indices_size, float v[], unsigned int i[]) : vertices_size(vertices_size), indices_size(indices_size)
{
	// WARNING : v is only the pointer to the first element of the array

	vertices = new float[vertices_size];
	for (int j = 0; j < vertices_size; j++) {
		std::cout << "*v: " << *v << std::endl;
		vertices[j] = *v;
		std::cout << "vertices[" << j << "] " << vertices[j] << std::endl;
		v++;
	}
	indices = new unsigned int[indices_size];
	for (int k = 0; k < indices_size; k++) {
		std::cout << "*i: " << *i << std::endl;
		indices[k] = *i;
		std::cout << "indices[" << k << "] " << indices[k] << std::endl;

		i++;
	}

	// Creates a new Vertex Array Object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s)
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Says that VBO is an id for an array of vertices, we are binding a buffer: a method that will handle the data

	glBufferData(GL_ARRAY_BUFFER, vertices_size * sizeof(float), vertices, GL_STATIC_DRAW); // copies user-defined data into the currently bound buffer
																				/*GL_STATIC_DRAW: the data will most likely not change at all or very rarely.
																				GL_DYNAMIC_DRAW : the data is likely to change a lot.
																				GL_STREAM_DRAW : the data will change every time it is drawn.
																				*/

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // again, the parameters needs to be passed between a bind and an unbind, here we bind to the vertices array
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size * sizeof(unsigned int), indices, GL_STATIC_DRAW); // Just need to change the type to ELEMENT_ARRAY_BUFFER

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // We say how to use the array
	/*
		The first parameter specifies which vertex attribute we want to configure. Remember that we specified the location of the position vertex attribute in the vertex shader with layout (location = 0).
		This sets the location of the vertex attribute to 0 and since we want to pass data to this vertex attribute, we pass in 0.
		The second specifies the size of the attribute, it's a vec3 => 3 float => size = 3
		Third specifies the type of data, GL_FLOAT
		4th specifies if data should be normalized
		The fifth argument is known as the stride and tells us the space between consecutive vertex attributes
		6th This is the offset of where the position data begins in the buffer. Since the position data is at the start of the data array this value is just 0.
	*/
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbinds the buffer once done
	glBindVertexArray(0); // We unbind the vertex array (our VAO) so we can bind it later for another object
	std::cout << "Model Initialized with a VBO and a EBO bound to a VAO" << std::endl;
}

Model::~Model()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
}

unsigned int * Model::getVAO()
{
	return &VAO;
}

int Model::get_indices_size()
{
	return indices_size;
}
