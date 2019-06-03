#pragma once
#include "Mesh.h"
#include "Animator.h"

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
		Joint rootJoint, int jointCount);
	~AnimatedMesh();

	/**
		Updates the animator time.
	*/
	void update(float delta_time);

	void draw(Shader* shader);

	std::vector<glm::mat4> getJointTransform();


	void doAnimation();

private:
	Animator animator;
	Joint rootJoint;
	int joinCount;

	void addJointsToArray(Joint headJoint, std::vector<glm::mat4> jointMatrices);
};

