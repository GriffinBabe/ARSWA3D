#pragma once

#include "Model.h"

class Triangle : public Model
{
public:
	Triangle(int vertices_size, int indices_size, float v[], unsigned int i[]);
	~Triangle();

	void changeDepht(float dz);
};

