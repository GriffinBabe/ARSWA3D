#include <vector>
#include "Mesh.h"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include "Shader.h"

class Model {
public: 

	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	//std::string directory;
	bool gammaCorrection;

	Model(char *path);
	void draw(Shader* shader);

private:
	std::string directory;

	unsigned int TextureFromFile(std::string path, std::string directory);

	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
											  std::string name);

};