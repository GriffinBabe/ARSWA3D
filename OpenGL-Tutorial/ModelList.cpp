#include "ModelList.h"

Model* ModelList::witch = NULL;
Model* ModelList::roof = NULL;
Model* ModelList::platform = NULL;
Model* ModelList::wall = NULL;

void ModelList::Init()
{
	witch = new Model("Models/witch/witch-toon2.obj", 0.0f, 0.42f);
	roof = new Model("Models/platform/roof.obj", 0.0f, 0.0f);
	platform = new Model("Models/platform/platform2.obj", 0.0f, 0.05f);
	wall = new Model("Models/platform/wall.obj", 0.0f, 0.0f);
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
