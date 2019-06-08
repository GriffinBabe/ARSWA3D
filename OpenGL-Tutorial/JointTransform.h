#ifndef JOINTTRANSFORM_H
#define JOINTTRANSFORM_H

#include <glm/glm.hpp>
#include "Quaternion.h"
#include <glm/gtc/matrix_transform.hpp>

class JointTransform
{
private:
	glm::vec3 position;
	Quaternion rotation;

	static glm::vec3 interpolate(glm::vec3 start, glm::vec3 end, float progression);
public:
	JointTransform(glm::vec3 pos, Quaternion quat);
	~JointTransform();

	glm::mat4 getLocalTransform();

	static JointTransform interpolate(JointTransform frameA, JointTransform frameB, float progression);
};


#endif