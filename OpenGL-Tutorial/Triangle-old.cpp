#include "Triangle-old.h"
#include <glad/glad.h>
#include <stdexcept>

Triangle::Triangle(glm::vec3 pos, glm::vec3 rot, Shader* shader, int vertices_size, int indices_size, float v[], unsigned int i[]) :
	Model(pos,rot,shader,vertices_size,indices_size,v,i)
{
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
