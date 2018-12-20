#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Model.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


Model::Model(glm::vec3 pos, glm::vec3 rot, Shader* shader, int vertices_size, int indices_size, float v[], unsigned int i[]) : position(pos), rotation(rot),
	vertices_size(vertices_size), indices_size(indices_size), shader(shader)
{
	// WARNING : v is only the pointer to the first element of the array

	vertices = new float[vertices_size];
	for (int j = 0; j < vertices_size; j++) {
		vertices[j] = *v;
		v++;
	}
	indices = new unsigned int[indices_size];
	for (int k = 0; k < indices_size; k++) {
		indices[k] = *i;
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // We say how to use the array
	glEnableVertexAttribArray(0);
	/*
		The first parameter specifies which vertex attribute we want to configure. Remember that we specified the location of the position vertex attribute in the vertex shader with layout (location = 0) in GLSL files.
		This sets the location of the vertex attribute to 0 and since we want to pass data to this vertex attribute, we pass in 0.
		The second specifies the size of the attribute, it's a vec3 => 3 float => size = 3
		Third specifies the type of data, GL_FLOAT
		4th specifies if data should be normalized
		The fifth argument is known as the stride and tells us the space between consecutive vertex attributes
		6th This is the offset of where the position data begins in the buffer. Since the position data is at the start of the data array this value is just 0.
	*/

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // We create another layer for our shading program with the texture coordinates
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbinds the buffer once done
	glBindVertexArray(0); // We unbind the vertex array (our VAO) so we can bind it later for another object



	glGenTextures(1, &texture); // creates an ID for a new texture
	glBindTexture(GL_TEXTURE_2D, texture); // so the next instructions will be referrend to this texture

	// <-------------------------- Currently bound Texture parameters --------------------------------->

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// 1st arg: texture type target
																		// 2nd arg: wrap axis
																		// 3rd arg: type of repetition
																			//GL_REPEAT: The default behavior for textures.Repeats the texture image.
																			//GL_MIRRORED_REPEAT : Same as GL_REPEAT but mirrors the image with each repeat.
																			//GL_CLAMP_TO_EDGE : Clamps the coordinates between 0 and 1. The result is that higher coordinates become clamped to the edge, resulting in a stretched edge pattern.
																			//GL_CLAMP_TO_BORDER : Coordinates outside the range are now given a user - specified border color.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Note: if we want to use GL_CLAMP_TO_BORDER we need to specify wich color we are using:
		//float borderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
		//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// Texture filtering, how are we going to draw a low rez texture on a very large model?
	// OpenGl uses filters: GL_NEAREST and GL_LINEAR and can be applied when magnifying GL_TEXTURE_MAG_FILTER or minifying GL_TEXTURE_MIN_FILTER
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Mimaps: we store multiple copies of the same texture but with different dimensions so we can apply more little textures for farest models and bigger for closest one
	// There is GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIMAP_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Mipmapping for magnifying has no effect so do not use it

	// <-------------------------- End of currently bound Texture parameters --------------------------------->

	int width, height, nrChannels; // number of color channels
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char* data = stbi_load("Textures/container.jpg", &width, &height, &nrChannels, 0); // loads the texture into a char array of bytes

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		/*
			Loads the texture to the currently bound texture
			1st arg: target texture type
			2nd arg: mimaplevel, 0 is the base level (the mimap is automaticly created by OpenGL)
			3rd arg: what kind of format
			4th and 5th arg: ...
			6th arg: Always 0 (some legacy stuff)
			7th and 9args: data type (a char is a byte)
			10th arg: the data
		*/
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::exception("Failed to load texture");
	}

	stbi_image_free(data); // Memory optimisation

	// You can bind multiple textures that you will use in the shader files

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("Textures/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); // to the currently bound texture
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);

}

Model::~Model()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	delete[] this->vertices;
	delete[] this->indices;
}

unsigned int * Model::getVAO()
{
	return &VAO;
}

int Model::get_indices_size()
{
	return indices_size;
}

void Model::render()
{
	this->bind_texture();

	// Vclip = Mprojection.Mview.Mmodel.Vlocal
		// Vlocal is the array of vertices, that are based around a central point
		// Mmodel is the transformation to world coordinates
		// Mview is the transformation for the camera
		// Mprojection

	glm::mat4 model;
	model = glm::translate(model, position);	
	model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	//model = glm::rotate(model, 3 * (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	this->shader->setMatrix4f("model",model);



	glBindVertexArray(VAO); // We bind those vertex we want to draw
		// Only if we are not using EBO: glDrawArrays(GL_TRIANGLES, 0, 3);	// 1st arg: primitive type we want to draw
																			// 2nd arg: starting index for drawing
																			// 3rd arg: how many vertices we want to draw
	//glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0);	// 1st arg: primite type we want to draw
	//														// 2nd arg: 6 indices so 6 vertices to draw
	//														// 3rd arg: type of indicies (unsigned int)
	//														// 4th arg: EBO offset (so we start at the first element of the indicies array in this case)
	//														// It takes the EBO bound to the VAO, and the VAO is currently bound with glBindVertexArray( vao );
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Model::bind_texture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	this->shader->setInt("texture1", 0); // texture 1 is GL_TEXTURE_0
	this->shader->setInt("texture2", 1); // texture 2 is GL_TEXTURE_1
}

glm::vec3 Model::get_position()
{
	return position;
}
