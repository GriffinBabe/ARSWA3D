#include "Joint.h"

Joint::Joint() : index(0), name(""), localBindTransform(glm::mat4()), children(std::vector<Joint>())
{

}
 
Joint::Joint(int index, std::string name, glm::mat4 bindLocalTransform)
	: index(index), name(name), localBindTransform(bindLocalTransform), children(std::vector<Joint>())
{

}

Joint::~Joint()
{
}

void Joint::addChild(Joint child)
{
	children.push_back(child);
}

void Joint::calcInverseBindTransform(const glm::mat4 & parentBindTranform)
{
	glm::mat4 bindTranform = glm::matrixCompMult(parentBindTranform, localBindTransform);
	inverseBindTransform = glm::inverse(bindTranform);
	for (Joint child : children) {
		child.calcInverseBindTransform(bindTranform);
	}
}
