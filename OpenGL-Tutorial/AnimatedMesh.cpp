#include "AnimatedMesh.h"


AnimatedMesh::AnimatedMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, int jointCount)
	: Mesh(vertices, indices, textures), animator(Animator(this)), jointCount(jointCount)
{

}

AnimatedMesh::~AnimatedMesh()
{
}

void AnimatedMesh::setRootJoint(Joint * root)
{
	if (rootJoint == nullptr) {
		rootJoint = root;
		rootJoint->calcInverseBindTransform(glm::mat4());
	}
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

void AnimatedMesh::addJointsToArray(Joint* headJoint, std::vector<glm::mat4> jointMatrices)
{
	jointMatrices[headJoint->index] = headJoint->getAnimatedTransform();
	for (Joint childJoint : headJoint->children) {
		addJointsToArray(&childJoint, jointMatrices);
	}
}

glm::mat4 AnimatedMesh::convertMatrix(const aiMatrix4x4 & matrix)
{
	glm::mat4 glmMatrice;

	glmMatrice[0][0] = matrix.a1;
	glmMatrice[0][1] = matrix.a2;
	glmMatrice[0][2] = matrix.a3;
	glmMatrice[0][3] = matrix.a4;

	glmMatrice[1][0] = matrix.b1;
	glmMatrice[1][1] = matrix.b2;
	glmMatrice[1][2] = matrix.b3;
	glmMatrice[1][3] = matrix.b4;

	glmMatrice[2][0] = matrix.c1;
	glmMatrice[2][1] = matrix.c2;
	glmMatrice[2][2] = matrix.c3;
	glmMatrice[2][3] = matrix.c4;

	glmMatrice[3][0] = matrix.d1;
	glmMatrice[3][1] = matrix.d2;
	glmMatrice[3][2] = matrix.d3;
	glmMatrice[3][3] = matrix.d4;

	return glm::mat4();
}
