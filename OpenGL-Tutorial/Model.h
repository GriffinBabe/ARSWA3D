#pragma once

#define STB_IMAGE_IMPLEMENTATION //Used so the stb_image uses relevant code and works like a .cpp file
#include "stb_image.h" // Image loader library
#include <memory>
#include <iostream>

class Model
{
public:
	Model(int vertices_size, int indices_size, float v[], unsigned int i[]);
	~Model();

	unsigned int* getVAO();
	int get_indices_size();

	void render();

protected:
	unsigned int VBO = 0;
	unsigned int VAO = 0;
	unsigned int EBO = 0;

	unsigned int texture = 0;

	float* vertices = nullptr; // Pointer to all my array so we can have a dynamic size array
	unsigned int* indices = nullptr; // Pointer to all my array so we can have a dynamic size array

	unsigned int vertices_size = 0;
	unsigned int indices_size = 0;

};

