#include "ModelList.h"
#include "ModelLoader.h"

Model* ModelList::witch = NULL;
Model* ModelList::roof = NULL;
Model* ModelList::platform = NULL;
Model* ModelList::wall = NULL;
std::vector<Model*> ModelList::loadedModels;

void ModelList::Init()
{
	ModelLoader* loader = ModelLoader::getInstance();

	witch = loader->loadModel("Models/witch/stick.fbx", true, .45f);
	witch->setRigged(true);
	witch->setOffsets(0.0f, -0.2f);
	RiggedMesh* mesh = dynamic_cast<RiggedMesh*>(witch->getMeshes()->at(0));
	loadedModels.push_back(witch);

	roof = loader->loadModel("Models/platform/roof.obj");
	roof->setOffsets(0.0f, 0.0f);
	loadedModels.push_back(roof);

	platform = loader->loadModel("Models/platform/platform2.obj");
	platform->setOffsets(0.0f, 0.0f);
	loadedModels.push_back(platform);


	wall = loader->loadModel("Models/platform/wall.obj");
	wall->setOffsets(0.0f, 0.0f);
	loadedModels.push_back(wall);
}

void ModelList::clear()
{
	delete witch; delete platform; delete roof; delete wall;
}

ModelList::~ModelList()
{
}

void ModelList::attachCharacter(Character* character)
{
	switch (character->id) {
		case (WITCH):
			ModelList::witch->addInstance(character);
			break;
	}
}
