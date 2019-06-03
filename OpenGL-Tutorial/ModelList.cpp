#include "ModelList.h"

Model* ModelList::witch = NULL;
Model* ModelList::roof = NULL;
Model* ModelList::platform = NULL;
Model* ModelList::wall = NULL;
std::vector<Model*> ModelList::loadedModels;

void ModelList::Init()
{
	witch = new Model("Models/witch/witch-toon2.obj", 0.0f, 0.42f);
	loadedModels.push_back(witch);
	roof = new Model("Models/platform/roof.obj", 0.0f, 0.0f);
	loadedModels.push_back(roof);
	platform = new Model("Models/platform/platform2.obj", 0.0f, 0.05f);
	loadedModels.push_back(platform);
	wall = new Model("Models/platform/wall.obj", 0.0f, 0.0f);
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
