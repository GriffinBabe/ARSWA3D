#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include <map>

#include "Model.h"


/**
	Singleton model loader using Assimp.


	@Author: Darius Couchard
	@Credit: leanopengl.com and TheThinMatrix
*/
class ModelLoader
{

public:

	static ModelLoader* getInstance();

	/**
		Loads a model using Assimp.

		@param pathFile, the file we want to load the model from
		@param axisFix, transforms the model coordinates from Blender coordinates to OpenGL coordinates
		@return the model from the given file
	*/
	Model* loadModel(const std::string& path, bool axisFix = false, float scale=1.0f);

private:
	ModelLoader();
	static ModelLoader* instance;
	
	// Parameter: transform model corrdinates from Blender coordinates to OpenGL coordinates.
	bool fixAxis = false;
	float axisScale = 1.0f;

	// Used to pass information through our functions
	std::string directory;
	std::vector<Texture> loadedTextures;

	/**
		Loads texture files from given path trough the stb_image.h library.
		@param path, the file name
		@param directory, the path to the directory the file currently sits in.
	*/
	unsigned int TextureFromFile(const char* path, std::string &directory);

	/**
		Process a node, is a recursive method that will call processMesh for each mesh in the file
		The method is overriden in the ModelLoader class as the behaviour is a little different.
	*/
	void processNode(std::vector<Mesh*>& meshes, aiNode *node, const aiScene *scene);

	/**
		Loads a mesh, preparing all vertices, indices and texture arrays.
	*/
	Mesh* processMesh(aiMesh *mesh, const aiScene *scene);


	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
		std::string TypeName);

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

	/**
		Converts an Assimp 4x4 Matrice to a glm::mat4 matrice

		@param matrix, the assimp matrice
		@return, the converted glm::mat4 matrice
	*/
	static glm::mat4 convertMatrix(const aiMatrix4x4 & matrix);


	/**
		Convers an Assimp 3D vector to a glm::vec3 vector

		@param, the assimp 3D vector
		@return, the converted glm::vec3 vector
	*/
	static glm::vec3 convertVector(const aiVector3D & vec);

	/**
		Checks if the model we want to load is a rigged model or
		a simple animationless model.

		@return the rootJoint node if it exists, a null pointer if it doesn't exits.
	*/
	aiNode* getRootJoint(const aiScene* scene);

	/**
		Recursively searches for a the root joint. The root joint necessarely
		have to be named "root" in the blender project before model exporting.
	*/
	aiNode* getRootJoint(aiNode* node);

	void loadAnimations(RiggedMesh* mesh, const aiScene* scene);


};

#endif