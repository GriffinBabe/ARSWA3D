#include "AnimatedMesh.h"


AnimatedMesh::AnimatedMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Joint rootJoint, int jointCount)
	: Mesh(vertices, indices, textures), animator(Animator(this)), rootJoint(rootJoint)
{
	rootJoint.calcInverseBindTransform(glm::mat4());
}

AnimatedMesh::~AnimatedMesh()
{
}

void AnimatedMesh::update(float delta_time)
{
	animator.update(delta_time);
}

void AnimatedMesh::draw(Shader * shader)
{
	//texture numbers that will be incremented
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++); // transfer unsigned int to stream
		else if (name == "texture_normal")
			number = std::to_string(normalNr++); // transfer unsigned int to stream
		else if (name == "texture_height")
			number = std::to_string(heightNr++); // transfer unsigned int to stream

												 // now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(shader->program_ID, (name + number).c_str()), i);
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

std::vector<glm::mat4> AnimatedMesh::getJointTransform()
{
	std::vector<glm::mat4> jointMatrices;
	addJointsToArray(rootJoint, jointMatrices);
	return jointMatrices;
}

void AnimatedMesh::doAnimation()
{
}

void AnimatedMesh::addJointsToArray(Joint headJoint, std::vector<glm::mat4> jointMatrices)
{
	jointMatrices[headJoint.index] = headJoint.getAnimatedTransform();
	for (Joint childJoint : headJoint.children) {
		addJointsToArray(childJoint, jointMatrices);
	}
}
