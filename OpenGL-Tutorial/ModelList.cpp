#include "ModelList.h"

Model* ModelList::witch = NULL;
Model* ModelList::roof = NULL;
Model* ModelList::platform = NULL;
Model* ModelList::wall = NULL;

void ModelList::Init()
{
	witch = new Model("Models/witch/witch-toon2.obj");
	roof = new Model("Models/platform/roof.obj");
	platform = new Model("Models/platform/platform2.obj");
	wall = new Model("Models/platform/wall.obj");
}

void ModelList::clear()
{
	delete witch; delete platform; delete roof; delete wall;
}

ModelList::~ModelList()
{
}
