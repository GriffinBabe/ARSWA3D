#pragma once

#include "Model.h"

class Triangle : public Model
{
public:
	Triangle(glm::vec3 position, glm::vec3 rot, Shader *shader, int vertices_size, int indices_size, float v[], unsigned int i[]);
	~Triangle();

	void changeDepht(float dz);
};

