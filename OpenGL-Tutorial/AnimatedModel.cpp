#include "AnimatedModel.h"
#include <stdexcept>
#include <map>

AnimatedModel::AnimatedModel(std::string path, float x_off, float y_off)
	: Model(path,x_off,y_off), meshes(std::vector<AnimatedMesh>()), boneMap(std::map<std::string,unsigned int>())
{
	loadModel(path);
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

AnimatedMesh AnimatedModel::processMesh(aiMesh * mesh, const aiScene * scene)
{
	// Not a very optimised way, might check later if
	// it causes big performance issues or not.
	// Creates a dummy mesh and take the 
	Mesh dummyMesh = Model::processMesh(mesh, scene);
	std::vector<Vertex> vertices = dummyMesh.vertices;
	std::vector<unsigned int> indices = dummyMesh.indices;
	std::vector<Texture> textures = dummyMesh.textures;

	// get all the bones from the mesh and sets them into our vector and map
	// set all the right boneID and weights to the right indices.
	std::vector<Joint> meshJoints = processBones(vertices, mesh);

	// Builds new Joints from our temporary meshJoints list.
	Joint rootJoint = buildBoneHierarchy(vertices, meshJoints, scene);

	AnimatedMesh nmesh(vertices, indices, textures, meshJoints.size());


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

Joint AnimatedModel::buildBoneHierarchy(const std::vector<Vertex>& vertices, const std::vector<Joint>& joints, const aiScene * scene)
{
	aiNode* rootBone = nullptr;

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
		throw std::exception("Couldn't find the root bone in mesh.");
	}

	// Gets the root joint from the map
	Joint rootJoint = joints[boneMap[rootBone->mName.data]];

	// We build the hierarchy from our joint vector and jointMap. 
	// We do not use the references to the joints vector elements but we copy them
	// and add them to the respective joint's children (I hope this is clear lol)
	//
	// The given rootJoint will be our rootJoint filled with other children joints,
	// each children joint can have also his children joint etc...
	recursiveBoneHierarchy(vertices, joints, rootJoint, rootBone);

	return rootJoint;
	
}

void AnimatedModel::recursiveBoneHierarchy(const std::vector<Vertex>& vertices,
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
