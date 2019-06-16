#include "JointTransform.h"



glm::vec3 JointTransform::interpolate(glm::vec3 start, glm::vec3 end, float progression)
{
	float x = start.x + (end.x - start.x) * progression;
	float y = start.y + (end.y - start.y) * progression;
	float z = start.z + (end.z - start.z) * progression;
	return glm::vec3(x, y, z);
}

JointTransform::JointTransform()
{
}

JointTransform::JointTransform(glm::vec3 pos, Quaternion quat)
{
	position = pos;
	rotation = quat;
}


JointTransform::~JointTransform()
{
}

glm::mat4 JointTransform::getLocalTransform()
{
	glm::mat4 matrix;
	glm::translate(matrix, position);
	matrix = glm::matrixCompMult(matrix, rotation.toRotationMatrix());
	return matrix;
}

JointTransform JointTransform::interpolate(JointTransform frameA, JointTransform frameB, float progression)
{
	glm::vec3 position = interpolate(frameA.position, frameB.position, progression);
	Quaternion rot = Quaternion::interpolate(frameA.rotation, frameB.rotation, progression);
	return JointTransform(position, rot);
}
