#pragma once

#include <memory>
#include <iostream>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct position
{
	float x;
	float y;
	float z;
};

class Model
{
public:
	Model(glm::vec3 pos, glm::vec3 rot, Shader* shader, int vertices_size, int indices_size, float v[], unsigned int i[]);
	~Model();

	unsigned int* getVAO();
	int get_indices_size();

	void render();
	void bind_texture();

	glm::vec3 get_position();

protected:
	unsigned int VBO = 0;
	unsigned int VAO = 0;
	unsigned int EBO = 0;

	unsigned int texture = 0;
	unsigned int texture2 = 0;

	float* vertices = nullptr; // Pointer to all my array so we can have a dynamic size array
	unsigned int* indices = nullptr; // Pointer to all my array so we can have a dynamic size array
	Shader* shader;

	glm::vec3 position;
	glm::vec3 rotation;

	unsigned int vertices_size = 0;
	unsigned int indices_size = 0;

};

