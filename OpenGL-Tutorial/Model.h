#pragma once

#include <memory>
#include <iostream>

class Model
{
public:
	Model(int vertices_size, int indices_size, float v[], unsigned int i[]);
	~Model();

	unsigned int* getVAO();
	int get_indices_size();
protected:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	float* vertices; // Pointer to all my array so we can have a dynamic size array
	unsigned int* indices; // Pointer to all my array so we can have a dynamic size array

	unsigned int vertices_size;
	unsigned int indices_size;

};

