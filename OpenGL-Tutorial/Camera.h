#pragma once

#include "glad/glad.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera(Shader* sha);

	~Camera();

	void set_matrices();
	void set_target(glm::vec3 tar);

private:
	glm::mat4 view;
	glm::mat4 projection;

	glm::vec3 position;
	glm::vec3 direction; // called direction but actually pointing in the opposite sense

	Shader* shader;
};

