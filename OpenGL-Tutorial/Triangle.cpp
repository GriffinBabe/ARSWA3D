#include "Triangle.h"
#include <glad/glad.h>
#include <stdexcept>

Triangle::Triangle(int vertices_size, int indices_size, float v[], unsigned int i[]) : Model(vertices_size,indices_size,v,i)
{
	std::cout << "Triangle initialized" << std::endl;
}


Triangle::~Triangle()
{
}

void Triangle::changeDepht(float dz)
{
	if (vertices_size % 3 != 0) { // We have more than 3 arguments per vertices
		std::exception("Wrong vertices size in Triangle::changeDepht");
	} 
	else {
		int number_of_vertices = vertices_size / 3; // as we have 3 arguments per vertice
		float* vertices_copy = vertices; // we create a copy of our pointer to our first argument of vertices
		vertices_copy++;
		vertices_copy++;
		for (int i = 2; i < vertices_size; i += 3) {
			*vertices_copy += dz;
			vertices_copy++;
			vertices_copy++;
			vertices_copy++;
		}
	}
}
