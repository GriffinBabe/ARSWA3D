#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "Mesh.h"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include "Shader.h"

class Entity;

class Model {
public: 

	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	//std::string directory;
	bool gammaCorrection;

	Model();
	Model(std::string path);
	void draw(Shader* shader, Entity* entity);

private:
	std::string directory;


	unsigned int TextureFromFile(const char* path, std::string &directory);

	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
											  std::string TypeName);

};

#endif