#pragma once

#include "Model.h"
#include "Mob.h"

class AnimatedModel : public Model
{
public:
	AnimatedModel(std::string path, float x_off, float y_off);
	AnimatedModel(std::vector<AnimatedMesh> meshes);
	AnimatedModel();
	~AnimatedModel();

	void draw(Shader* shader, Entity* entity);

private:
	std::vector<AnimatedMesh> meshes;
};