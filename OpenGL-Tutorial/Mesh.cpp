#include "Mesh.h"


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
	: vertices(vertices), indices(indices), textures(textures)
{
	setupMesh();
}

Mesh::~Mesh()
{
}

void Mesh::draw(Shader * shader)
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

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// We set the data reading settings on the first element of the structure: glm::vec3 position
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW); 

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


	// Vertex Positions
	glEnableVertexAttribArray(0);
	// Gives the data into our shader as the first layer of data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);


	// Vertex Normals
	glEnableVertexAttribArray(1);
	// Gives the data into our shader as the second layer of data
	// offsetof gives the offset between the start of the array Struct and the beginning of the given variable of the struct
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	glEnableVertexAttribArray(2);
	// Gives the data into our shader as the third layer of data
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
}


void RiggedMesh::setRootJoint(Joint root)
{
	rootJoint = root;
}

std::vector<glm::mat4> RiggedMesh::getJointTransform()
{
	std::vector<glm::mat4> jointMatrices;
	addJointsToArray(&rootJoint, jointMatrices);
	return jointMatrices;
}

RiggedMesh::RiggedMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, int jointCount)
	: Mesh(vertices, indices, textures), jointCount(jointCount), animations(std::map<std::string, Animation>())
{

}

void RiggedMesh::addJointsToArray(Joint* headJoint, std::vector<glm::mat4> jointMatrices)
{
	jointMatrices[headJoint->index] = headJoint->getAnimatedTransform();
	for (Joint childJoint : headJoint->children) {
		addJointsToArray(&childJoint, jointMatrices);
	}
}

RiggedMesh::~RiggedMesh()
{
}