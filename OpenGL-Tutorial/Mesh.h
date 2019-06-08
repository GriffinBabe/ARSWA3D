#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Joint.h"
#include "Shader.h"
#include "Animator.h"

#define JOINT_PER_VERTEX 3

struct Vertex {

	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Bitangent;
	glm::vec3 Tangent;

	int boneIds[JOINT_PER_VERTEX] = { 0 };
	float boneWeigths[JOINT_PER_VERTEX] = { 0 };

	void addBoneId(int id) {
		for (int i = 0; i < JOINT_PER_VERTEX; i++) {
			if (boneIds[i] == 0) {
				boneIds[i] = id;
			}
		}
	}

	void addBoneWeigth(float w) {
		for (int i = 0; i < JOINT_PER_VERTEX; i++) {
			if (boneWeigths[i] == 0) {
				boneWeigths[i] = w;
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

private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};

class RiggedMesh : public Mesh {

public:

	RiggedMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, int jointCount);

	/**
		Updates the animator time.
	*/
	void update(float delta_time);
	void doAnimation();

	std::vector<int>& getJointIds() { return jointIds; }
	std::vector<float>& getVertexWeigths() { return vertexWeights; }


	void setRootJoint(Joint* root) { rootJoint = root; }
	std::vector<glm::mat4> getJointTransform();

private:
	/**
		The ID of the linked joint of each corresponding vertex from the vertices vector
		There are 3 jointIds per vertex. So this array will have 3x more elements than the vertices vector
	*/
	std::vector<int> jointIds;

	/**
		Same as jointIds, but this will contain the respective weight of it.
	*/
	std::vector<float> vertexWeights;

	Animator animator;
	Joint* rootJoint;
	int jointCount;

	void addJointsToArray(Joint* headJoint, std::vector<glm::mat4> jointMatrices);
};

#endif // !MESH_H