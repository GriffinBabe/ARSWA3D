#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "Mesh.h"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include "Shader.h"
#include "Observer.h"

class Entity;

class Model : public Observer{
public: 

	Model();

	/**
		NB: x_off are the distance between the center of the mesh (ofter located at the center bottom) to
		what we might use as the center in the model.
	*/
	Model(std::string path, float x_off, float y_off);
	void draw(Shader* shader, float delta_time);
	float x_off = 0.0f; float y_off;

	/**
		Removes one of the entities.
	*/
	void removeEntity(Entity* entity);
	void addEntity(Entity* entity);

	void onNotify(Entity& entitiy, EEvent event) override;
protected:
	std::string directory;

protected:

	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	//std::string directory;
	bool gammaCorrection;


	std::vector<Entity*> entities;


	unsigned int TextureFromFile(const char* path, std::string &directory);

	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
											  std::string TypeName);
};

#endif