#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in ivec3 in_jointIndices; // Wich bones does affect this vertex
layout (location = 4) in vec3 in_weights; // With what weights does each bone affect

const int MAX_JOINTS = 100;
const int MAX_WEIGHTS = 3;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 jointTransforms[MAX_JOINTS]; // Joint transformations matrices

void main()
{

	vec4 totalLocalPos = vec4(0.0);
	vec4 totalNormal = vec4(0.0);

	for (int i = 0; i < MAX_WEIGHTS; i++) {
		mat4 jointTransform = jointTransforms[in_jointIndices[i]]; // this joint transformation matrix
		vec4 posePosition = jointTransform * vec4(aPos, 1.0);
		totalLocalPos += posePosition * in_weights[i];

		vec4 worldNormal = jointTransform * vec4(aPos, 1.0);
		totalNormal += worldNormal * in_weights[i];
	}

	FragPos = vec3(model * totalLocalPos);
    Normal = mat3(transpose(inverse(model))) * vec3(totalNormal);  
    TexCoords = aTexCoords;
    gl_Position = projection * view * vec4(FragPos, 1.0);
}