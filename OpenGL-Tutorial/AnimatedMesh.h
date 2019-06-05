#pragma once
#include "Mesh.h"
#include "Animator.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

/**

	AnimatedModel is an animable mesh.
	This implementation  directly comes from TheThinMatrix
	
	@Author GriffinBabe

	Credit: TheThinMatrix
	https://github.com/TheThinMatrix/OpenGL-Animation
*/

class AnimatedMesh : public Mesh
{
public:
	const Shader animationShader;

	AnimatedMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures,
		int jointCount);
	~AnimatedMesh();

	void setRootJoint(Joint* root);

	/**
		Updates the animator time.
	*/
	void update(float delta_time);

	void draw(Shader* shader);

	std::vector<glm::mat4> getJointTransform();

	std::vector<int>& getJointIds() { return jointIds; }
	std::vector<float>& getVertexWeigths() { return vertexWeights; }

	void doAnimation();

	static glm::mat4 convertMatrix(const aiMatrix4x4 & matrix);

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

