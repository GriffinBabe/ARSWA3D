#pragma once

#include "Model.h"
#include "AnimatedMesh.h"
#include "Mob.h"

class AnimatedModel : public Model
{
public:
	AnimatedModel(std::string path, float x_off, float y_off);
	AnimatedModel();
	~AnimatedModel();

	void draw(Shader* shader, Entity* entity);

private:
	std::vector<AnimatedMesh> meshes;

	/**
		Overiddes the Model::loadModel() function as we also need to import animation.
	*/
	void loadModel(const std::string &path);

	/**
		Same as Model::processNode, but the method will call an AnimatedModel function.
	*/
	void processNode(aiNode* node, const aiScene* scene);

	/**
		Same as Model::processMesh, but the method will call an AnimatedModel function.
	*/
	AnimatedMesh processMesh(aiMesh* mesh, const aiScene* scene);

	/**
		Iterates over the mesh bones.

		- Each bone will be indexed according to it's name in boneMap.
		- From each bone a joint will be created with its name and matrice, and added to a Joint vector
		- From each bone we will add the bone id and respective weight to the respective mesh vertex
	*/
	std::vector<Joint> processBones(std::vector<Vertex>& vertices, aiMesh* mesh);

	/**
		First part of the hierarchy building, this method will search through all
		the scene for the rootJoint. Then will call the recursive method 'recursiveBoneHierarchy'
		to build the Project.

		Credit for this solution: 
		https://stackoverflow.com/questions/51225072/construct-assimp-bone-hierarchy-beginning-at-the-root
	*/
	Joint buildBoneHierarchy(const std::vector<Vertex>& vertices, const std::vector<Joint>& joints, 
		const aiScene* scene);


	/**
		Recursievely adds to our joint they're childrens.	
	*/
	void recursiveBoneHierarchy(const std::vector<Vertex>& vertices, 
		const	std::vector<Joint>& joints, Joint& parentJoint, aiNode* boneNode);

	/**
		boneMap, very usefull in recursiveBoneHierarchy and processBone methods to
		find the created joint through an aiNode name. And also to know if an aiNode
		corresponds to a joint or not.
	*/
	std::map<std::string, unsigned int> boneMap;
};