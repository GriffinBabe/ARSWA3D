#pragma once

#include "Model.h"
#include "AnimatedMesh.h"
#include "Mob.h"

class AnimatedModel : public Model
{
public:
	AnimatedModel(std::string path, float x_off, float y_off);
	AnimatedModel();
	~AnimatedModel();

	void draw(Shader* shader, Entity* entity);

private:
	std::vector<AnimatedMesh> meshes;

	/**
		Overiddes the Model::loadModel() function as we also need to import animation.
	*/
	void loadModelAnimations(const std::string &path);

};

