#include "Model.h"
#include "stb_image.h"

Model::Model(char * path) : meshes(std::vector<Mesh>())
{
	loadModel(path);
}

void Model::draw(Shader * shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i].draw(shader);
	}
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs); // Triangulate means our meshes is imported in all triangles (as it's how opengl renders stuff) flipuvs is to flip the textures
		//	aiProcess_GenNormals: actually creates normals for each vertex if the model didn't contain normal vectors.
		//	aiProcess_SplitLargeMeshes : splits large meshes into smaller sub - meshes which is useful if your rendering has a maximum number of vertices allowed and can only process smaller meshes.
		//	aiProcess_OptimizeMeshes : actually does the reverse by trying to join several meshes into one larger mesh, reducing drawing calls for optimization.

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode * node, const aiScene * scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;

		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;


		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else {
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}

		vector.x = mesh->mTangents[i].x;
		vector.y = mesh->mTangents[i].y;
		vector.z = mesh->mTangents[i].z;
		vertex.Tangent = vector;
		// bitangent
		vector.x = mesh->mBitangents[i].x;
		vector.y = mesh->mBitangents[i].y;
		vector.z = mesh->mBitangents[i].z;
		vertex.Bitangent = vector;

		vertices.push_back(vertex);
	}


	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material,
																aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = loadMaterialTextures(material,
																 aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	}

	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string name)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);
		Texture texture;
		texture.id = TextureFromFile(str.C_Str(), directory);
		//texture.type = typeName;
		texture.path = str.C_Str();
		textures.push_back(texture);
		textures_loaded.push_back(texture);
	}
	return textures;
}

unsigned int Model::TextureFromFile(std::string path, std::string directory) {
	unsigned int texture = 1;
	glGenTextures(1, &texture); // creates an ID for a new texture
	glBindTexture(GL_TEXTURE_2D, texture); // so the next instructions will be referrend to this texture

	// <-------------------------- Currently bound Texture parameters --------------------------------->

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// 1st arg: texture type target
																		// 2nd arg: wrap axis
																		// 3rd arg: type of repetition
																			//GL_REPEAT: The default behavior for textures.Repeats the texture image.
																			//GL_MIRRORED_REPEAT : Same as GL_REPEAT but mirrors the image with each repeat.
																			//GL_CLAMP_TO_EDGE : Clamps the coordinates between 0 and 1. The result is that higher coordinates become clamped to the edge, resulting in a stretched edge pattern.
																			//GL_CLAMP_TO_BORDER : Coordinates outside the range are now given a user - specified border color.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Note: if we want to use GL_CLAMP_TO_BORDER we need to specify wich color we are using:
		//float borderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
		//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// Texture filtering, how are we going to draw a low rez texture on a very large model?
	// OpenGl uses filters: GL_NEAREST and GL_LINEAR and can be applied when magnifying GL_TEXTURE_MAG_FILTER or minifying GL_TEXTURE_MIN_FILTER
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Mimaps: we store multiple copies of the same texture but with different dimensions so we can apply more little textures for farest models and bigger for closest one
	// There is GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIMAP_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Mipmapping for magnifying has no effect so do not use it

	// <-------------------------- End of currently bound Texture parameters --------------------------------->

	int width, height, nrChannels; // number of color channels
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char* data = stbi_load("Textures/container.jpg", &width, &height, &nrChannels, 0); // loads the texture into a char array of bytes

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		/*
			Loads the texture to the currently bound texture
			1st arg: target texture type
			2nd arg: mimaplevel, 0 is the base level (the mimap is automaticly created by OpenGL)
			3rd arg: what kind of format
			4th and 5th arg: ...
			6th arg: Always 0 (some legacy stuff)
			7th and 9args: data type (a char is a byte)
			10th arg: the data
		*/
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::exception("Failed to load texture");
	}

	stbi_image_free(data); // Memory optimisation

	return texture;
}