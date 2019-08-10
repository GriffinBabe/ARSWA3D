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
#include "Animation.h"

#define MAX_JOINTS_PER_VERTEX 3
#define MAX_JOINTS 150

struct Vertex {

	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Bitangent;
	glm::vec3 Tangent;

	int boneIds[MAX_JOINTS_PER_VERTEX] = { 0 };
	float boneWeights[MAX_JOINTS_PER_VERTEX] = { 0 };

	void addBoneId(int id) {
		for (int i = 0; i < MAX_JOINTS_PER_VERTEX; i++) {
			if (boneIds[i] == 0) {
				boneIds[i] = id;
			}
		}
	}

	void addBoneWeigth(float w) {
		for (int i = 0; i < MAX_JOINTS_PER_VERTEX; i++) {
			if (boneWeights[i] == 0) {
				boneWeights[i] = w;
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
	virtual ~Mesh();	
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	virtual void draw(Shader* shader);

protected:
	virtual void setupMesh();

private:
	virtual void dummyPolymorphic() {};
	unsigned int VAO, VBO, EBO;
};

class RiggedMesh : public Mesh {

public:

	RiggedMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, int jointCount);
	virtual ~RiggedMesh() override;
	
	std::vector<int>& getJointIds() { return jointIds; }
	std::vector<float>& getVertexWeigths() { return vertexWeights; }

	Joint& getRootJoint() { return rootJoint; }

	void setRootJoint(Joint root);
	void setAnimations(std::map<std::string,Animation> a) { animations = a; }
	std::map<std::string, Animation>& getAnimations() { return animations; }

	void draw(Shader* shader) override;

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

	Joint rootJoint;
	int jointCount;

	std::map<std::string, Animation> animations;

	void addJointsToArray(Joint& headJoint, std::vector<glm::mat4>& jointMatrices);

	void dummyPolymorphic() override {};

protected:
	void setupMesh() override;
};

#endif // !MESH_H