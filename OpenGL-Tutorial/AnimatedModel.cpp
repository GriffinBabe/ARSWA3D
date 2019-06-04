#include "AnimatedModel.h"
#include <map>

AnimatedModel::AnimatedModel(std::string path, float x_off, float y_off)
	: Model(path,x_off,y_off), meshes(std::vector<AnimatedMesh>()), boneMap(std::map<std::string,unsigned int>())
{
	loadModelAnimations(path);
}

AnimatedModel::AnimatedModel()
{
}


AnimatedModel::~AnimatedModel()
{
}

void AnimatedModel::draw(Shader * shader, Entity * entity)
{
	glm::mat4 model = glm::mat4(1.0f);
	if (entity != nullptr) {
		model = glm::translate(model, glm::vec3(entity->x - x_off, entity->y - y_off, entity->z));
		model = glm::rotate(model, glm::radians(entity->rotX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(entity->rotY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(entity->rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(entity->scaleX, entity->scaleY, entity->scaleZ));
	}
	else {
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	}
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	shader->setMatrix4f("model", model);
	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i].draw(shader);
	}
}

void AnimatedModel::loadModel(const std::string &path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// Triangulate means our meshes is imported in all triangles (as it's how opengl renders stuff) flipuvs is to flip the textures
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

void AnimatedModel::processNode(aiNode * node, const aiScene * scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}


AnimatedMesh AnimatedModel::processMesh(aiMesh * mesh, const aiScene * scene)
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
		std::vector<Texture> diffuseMaps = Model::loadMaterialTextures(material,
			aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = loadMaterialTextures(material,
			aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	}

	std::vector<Joint> meshJoints = processBones(mesh); // get all the bones from the mesh

	AnimatedMesh nmesh(vertices, indices, textures, meshJoints);
	buildBoneHierarchy(vertices.size(), meshJoints, scene, nmesh);



	// TODO: set the vertices joint ids and weights.


	return nmesh;
}

std::vector<Joint> AnimatedModel::processBones(std::vector<Vertex>& vertices, aiMesh* mesh)
{
	std::vector<Joint> joints;
	if (mesh->HasBones()) {
		
		for (unsigned int i = 0; i < mesh->mNumBones; i++) {
			aiBone* bone = mesh->mBones[i];
			std::string bonename = bone->mName.data;
			glm::mat4 matrice = AnimatedMesh::convertMatrix(bone->mOffsetMatrix);
			boneMap[bonename] = i;
			joints.push_back(Joint((int)i, bonename, matrice));
			for (unsigned int j = 0; j < bone->mNumWeights; j++) {
				aiVertexWeight weigth = bone->mWeights[j];

				// Adds the bone id and weight to the right vertex
				vertices[weigth.mVertexId].addBoneId(i);
				vertices[weigth.mVertexId].addBoneWeigth(weigth.mWeight);
			}
		}
	}
	return std::vector<Joint>();
}

void AnimatedModel::buildBoneHierarchy(const std::vector<Vertex>& vertices, const std::vector<Joint>& joints, const aiScene * scene, AnimatedMesh& mesh)
{
	aiNode* rootBone;

	for (unsigned int i = 0; i < scene->mRootNode->mNumChildren; i++) {
		aiNode* node = scene->mRootNode->mChildren[i];
		if (boneMap.find(node->mName.data) != boneMap.end()) {
			aiNode* parent = node->mParent;
			if (parent) {
				if (boneMap.find(parent->mName.data) == boneMap.end()) {
					// We found the root node
					rootBone = parent;
				}
				else {
					// This isn't the root node
					continue;
				}
			}
		}
	}

	if (!rootBone) {
		std::cout << "ASSIMP::Error couldn't find the root bone" << std::endl;
		return;
	}

	std::vector<Joint>::iterator it = joints.begin();
	
	recursiveBoneHierarchy(vertices, joints, );

}

void AnimatedModel::recursiveBoneHierarchy(const std::vector<Vertex>& vertices,
	const std::vector<Joint>& joints, Joint& parentJoint, aiNode * boneNode)
{
	std::string name = boneNode->mName.data;
	// Checks if the given node is a bone
	if (boneMap.find(name) != boneMap.end()) {
		// at this point we know boneNode is a Joint
		// trough our boneMap, we know the id of the joint from the boneNode name.
		unsigned int boneId = boneMap[name];
		// We set the vertex bone id and weight
		
		// We use that id to find the bone and sets it to the parentJoint childrens
		parentJoint.addChild(joints[boneId]);

	}


	joints[boneMap[]]
	return std::vector<Joint>();
}
