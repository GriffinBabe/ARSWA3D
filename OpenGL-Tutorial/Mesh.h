#ifndef MESH_H
#define MESH_H

#define JOINT_PER_VERTEX;

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>

/*
	NOTE on Stucts:

	Vertex vertex;
	vertex.Position  = glm::vec3(0.2f, 0.4f, 0.6f);
	vertex.Normal    = glm::vec3(0.0f, 1.0f, 0.0f);
	vertex.TexCoords = glm::vec2(1.0f, 0.0f);
	// = [0.2f, 0.4f, 0.6f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f];

	Structures have the advantage to have a sequential memory layout
*/

struct Vertex {

	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Bitangent;
	glm::vec3 Tangent;

	int[JOINT_PER_VERTEX] boneIds = { 0 };
	float[JOINT_PER_VERTEX] boneWeigths = { 0 };

	void addBoneId(int id) {
		for (int i = 0; i < JOINT_PER_VERTEX; i++) {
			if (boneIds[i] == 0) {
				bonesIds[i] == id;
			}
		}
	}

	void addBoneWeigth(float w) {
		for (int i = 0; i < JOINT_PER_VERTEX; i++) {
			if (boneWei[i] == 0) {
				bonesIds[i] == id;
			}
		}
	}

};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	~Mesh();

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	
	void draw(Shader* shader);
protected:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};

#endif // !MESH_H