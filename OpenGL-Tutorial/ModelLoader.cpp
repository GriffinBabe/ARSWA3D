#include "ModelLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const char* const ROOT_BONE_NAME = "root";

ModelLoader* ModelLoader::instance = nullptr;

ModelLoader* ModelLoader::getInstance()
{
	if (!instance) {
		ModelLoader::instance = new ModelLoader();
	}
	return instance;
}

ModelLoader::ModelLoader() : loadedTextures(std::vector<Texture>())
{

}

unsigned int ModelLoader::TextureFromFile(const char* path, std::string &directory)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;

	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

std::vector<Texture> ModelLoader::loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < loadedTextures.size(); j++) {
			if (std::strcmp(loadedTextures[j].path.data(), str.C_Str()) == 0) {
				textures.push_back(loadedTextures[j]);
				skip = true;
				break;
			}
		}
		if (!skip) {
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			loadedTextures.push_back(texture);
		}
	}
	std::cout << textures.size() << std::endl;
	return textures;
}

Model * ModelLoader::loadModel(const std::string& path, bool axisFix, float scale)
{
	fixAxis = axisFix;
	axisScale = scale;

	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return new Model();
	}
	directory = path.substr(0, path.find_last_of('/'));


	std::vector<Mesh*> meshes;

	processNode(meshes, scene->mRootNode, scene);

	/*
	std::vector<Mesh> meshes2;
	for (Mesh* m : meshes) {
		meshes2.push_back(*m);
		delete m;
	}
	*/

	return new Model(meshes);
}

void ModelLoader::processNode(std::vector<Mesh*>& meshes, aiNode * node, const aiScene * scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		
		meshes.push_back(processMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(meshes, node->mChildren[i], scene);
	}
}

Mesh* ModelLoader::processMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;

		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x * axisScale;
		if (!fixAxis) {
			vector.y = mesh->mVertices[i].y * axisScale;
			vector.z = mesh->mVertices[i].z * axisScale;
		}
		else {
			vector.y = mesh->mVertices[i].z * axisScale;
			vector.z = - mesh->mVertices[i].y * axisScale;
		}
		vertex.Position = vector;

		vector.x = mesh->mNormals[i].x * axisScale;
		if (!fixAxis) {
			vector.y = mesh->mNormals[i].y * axisScale;
			vector.z = mesh->mNormals[i].z * axisScale;
		}
		else {
			vector.y = mesh->mNormals[i].z * axisScale;
			vector.z = - mesh->mNormals[i].y * axisScale;

		}
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

		vector.x = mesh->mTangents[i].x * axisScale;
		if (!fixAxis) {
			vector.y = mesh->mTangents[i].y * axisScale;
			vector.z = mesh->mTangents[i].z * axisScale;
		}
		else {
			vector.y = mesh->mTangents[i].z * axisScale;
			vector.z = - mesh->mTangents[i].y * axisScale;
		}
		vertex.Tangent = vector;
		// bitangent
		vector.x = mesh->mBitangents[i].x * axisScale;
		if (!fixAxis) {
			vector.y = mesh->mBitangents[i].y * axisScale;
			vector.z = mesh->mBitangents[i].z * axisScale;
		}
		else {
			vector.y = mesh->mBitangents[i].z * axisScale;
			vector.z = - mesh->mBitangents[i].y * axisScale;
		}
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

	// Processes the bones, filling the map
	if (mesh->mNumBones > 0) {
		processBones(vertices, mesh);
		// Can't find root join for the witch
		if (getRootJoint(scene->mRootNode)!=nullptr) {
			// get all the bones from the mesh and sets them into our vector and map
			// set all the right boneID and weights to the right indices.
			std::vector<Joint> meshJoints = processBones(vertices, mesh);
			// Builds new Joints from our temporary meshJoints list.
			Joint rootJoint = buildBoneHierarchy(vertices, meshJoints, scene);
			RiggedMesh* rmesh = new RiggedMesh(vertices, indices, textures, meshJoints.size());
			rmesh->setRootJoint(rootJoint);
			loadAnimations(rmesh, scene);
			return rmesh;
		}
	}
	return new Mesh(vertices, indices, textures);
	// TODO: set the vertices joint ids and weights.
}

std::vector<Joint> ModelLoader::processBones(std::vector<Vertex>& vertices, aiMesh* mesh)
{
	std::vector<Joint> joints;
	if (mesh->HasBones()) {

		for (unsigned int i = 0; i < mesh->mNumBones; i++) {
			aiBone* bone = mesh->mBones[i];
			std::string bonename = bone->mName.data;
			glm::mat4 matrice = convertMatrix(bone->mOffsetMatrix);
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
	return joints;
}

Joint ModelLoader::buildBoneHierarchy(const std::vector<Vertex>& vertices, const std::vector<Joint>& joints, const aiScene * scene)
{
	aiNode* rootBone = nullptr;

	rootBone = getRootJoint(scene->mRootNode);
	
	if (!rootBone) {
		throw std::exception("Couldn't find the root bone in mesh.");
	}
	else {
		// Gets the root joint from the map
		Joint rootJoint = joints[boneMap[rootBone->mName.data]];

		// We build the hierarchy from our joint vector and jointMap. 
		// We do not use the references to the joints vector elements but we copy them
		// and add them to the respective joint's children (I hope this is clear lol)
		//
		// The given rootJoint will be our rootJoint filled with other children joints,
		// each children joint can have also his children joint etc...
		recursiveBoneHierarchy(vertices, joints, rootJoint, rootBone);

		// Warning, for the 'Witch' the root joint has the 'spine05' name, but it's children also is name 'spine05'
		// Maybe I should force the name of the root joint to 'root'
		
		rootJoint.setName(ROOT_BONE_NAME);
		return rootJoint;
	}
}

void ModelLoader::recursiveBoneHierarchy(const std::vector<Vertex>& vertices,
	const std::vector<Joint>& joints, Joint& parentJoint, aiNode * boneNode)
{
	std::string name = boneNode->mName.data;
	// Checks if the given node is a bone we registered earlier
	if (boneMap.find(name) != boneMap.end()) {
		// at this point we know boneNode is a Joint
		// trough our boneMap, we know the id of the joint from the boneNode name.
		unsigned int boneId = boneMap[name];

		Joint childrenJoint = joints.at(boneId);
		for (unsigned int i = 0; i < boneNode->mNumChildren; i++) {
			recursiveBoneHierarchy(vertices, joints, childrenJoint, boneNode->mChildren[i]);
		}

		// We use that id to find the bone and sets it to the parentJoint childrens
		// Adds the children joint to the parent joint
		parentJoint.addChild(childrenJoint);
	}
}


glm::mat4 ModelLoader::convertMatrix(const aiMatrix4x4 & matrix)
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

glm::vec3 ModelLoader::convertVector(const aiVector3D & vec)
{
	glm::vec3 glmVec;
	glmVec.x = vec.x;
	glmVec.y = vec.y;
	glmVec.z = vec.z;
	return glmVec;
}

aiNode * ModelLoader::getRootJoint(const aiScene* scene)
{
	/*
	aiNode* rootNode = scene->mRootNode;
	aiNode* modelNode = rootNode->mChildren[0]; // In our file, the animation model is always the first element
	for (unsigned int i = 0; i < modelNode->mNumChildren; i++) {
		aiNode* node = modelNode->mChildren[i];
		if (std::string(node->mName.data) == ROOT_BONE_NAME) {
			return node;
		}
	}
	*/

	aiNode* rootNode = scene->mRootNode;
	for (unsigned int i = 0; i < rootNode->mNumChildren; i++) {
		aiNode* node = rootNode->mChildren[i];
		if (std::string(node->mName.data) == ROOT_BONE_NAME) {
			return node;
		}
	}

	return nullptr;
}

aiNode * ModelLoader::getRootJoint(aiNode * node)
{
	if (std::string(node->mName.data) == ROOT_BONE_NAME) {
		return node;
	}
	else if (node->mNumChildren > 0) {
		for (unsigned int i = 0; i < node->mNumChildren; i++) {
			aiNode* children = getRootJoint(node->mChildren[i]);
			if (children != nullptr) {
				if (std::string(children->mName.data) == ROOT_BONE_NAME) {
					return children;
				}
			}
		}
	}
	return nullptr;
}

void ModelLoader::loadAnimations(RiggedMesh* mesh, const aiScene * scene)
{
	std::map<std::string,Animation> animations;

	for (unsigned int i = 0; i < scene->mNumAnimations; i++) {
		aiAnimation* animation = scene->mAnimations[i];
		std::string animationName = animation->mName.data;
		std::vector<KeyFrame> frames;

		float timePerFrame = 1 / animation->mTicksPerSecond;
		float durationInSeconds = animation->mDuration * timePerFrame;
		
		float time = 0;
		// mDuration is the number of ticks
		// mTicksPerSecond is the number of ticks per second
		for (unsigned int f = 0; f < ceil(animation->mDuration); f++) {
			std::map<std::string, JointTransform> transformMap;
			for (unsigned int c = 0; c < animation->mNumChannels; c++) {
				aiNodeAnim* nodeAnim = animation->mChannels[c];
				// The nodeAnim corresponds to JointTransform
				// Name of the bone
				std::string name(nodeAnim->mNodeName.data);
				aiVector3D position = nodeAnim->mPositionKeys[f].mValue;
				aiQuaternion rotation = nodeAnim->mRotationKeys[f].mValue;
				Quaternion quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
				// We have the time, position, rotation from a bone
				// We just have to fill our transformMap with a new JointTransform
				JointTransform transform(convertVector(position), quaternion);
				transformMap[name] = transform;
			}
			//  The new keyFrame
			KeyFrame frame(time, transformMap);
			frames.push_back(frame);
			time += timePerFrame;
		}
		Animation nAnimation(durationInSeconds, frames);
		animations[animationName] = nAnimation;
	}
	mesh->setAnimations(animations);
	// Our animations vector is now complete
	
}



