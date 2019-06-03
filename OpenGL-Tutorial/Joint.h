#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Joint
{
private:

	glm::mat4 animatedTransform;
	const glm::mat4 localBindTransform;
	glm::mat4 inverseBindTransform;
	

public:
	Joint(int index, std::string name, glm::mat4 bindLocalTransform);
	~Joint();

	/**
		Adds a child to the hierarchy.
	*/
	void addChild(Joint child);

	/**
		The animated transform is the transformation that will be loaded in
		the shader. It will be used to deform the "skin" vertices.

		@return The transformation matrix of the joint which is used to deform
				associated vertices of the skin in the shaders
	*/
	glm::mat4& getAnimatedTransform() { return animatedTransform; }

	/**
		Called during setup, Calculates the model-space bind transformation of this joint.
	*/
	glm::mat4& getInverseBindTransform() { return inverseBindTransform; }

	/**
		Allows all the important "Joint Transforms" to be set by the animator.
	*/
	void setAnimationTransform(const glm::mat4& antrans) { animatedTransform = antrans; }

	/**
		This is called during set-up, after the joints hierarchy has been
		created. This calculates the model-space bind transform of this joint.
	*/
	void calcInverseBindTransform(const glm::mat4& parentBindTranform);

	const int index; // Index used as ID
	const std::string name;
	std::vector<Joint> children;

};

