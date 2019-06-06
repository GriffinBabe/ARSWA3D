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

	witch = loader->loadModel("Models/witch/witch-toon2.obj");
	witch->setOffsets(0.0f, 0.42f);
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
			ModelList::witch->addEntity(character);
			break;
	}
}
