#ifndef CAMERA_H
#define CAMERA_H


#include "glad/glad.h"
#include "GLFW/glfw3.h"
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

	void set_camera_dx(int direction);
	void set_camera_dz(int direction);

	void change_yaw_offset(float dy);
	void change_pitch_offset(float dp);

	void set_sprint(bool sprint);

	void adapt_perspective(GLFWwindow* window);
	void switch_free();

private:
	glm::mat4 view;
	glm::mat4 projection;

	
	glm::vec3 position;
	glm::vec3 worldUp;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;
	glm::vec3 cameraFront;

	float pitch = 0.0f	, yaw = -90.0f;

	float camera_speed = 3.0f;
	float dx = 0, dz = 0;
	float delta_time = 0;
	float last_frame = 0;

	bool free = false;

	Shader* shader;

};

#endif // !CAMERA_H
