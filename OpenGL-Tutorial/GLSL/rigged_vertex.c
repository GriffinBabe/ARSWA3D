#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in ivec3 in_jointIndices; // Wich bones does affect this vertex
layout (location = 4) in vec3 in_weights; // With what weights does each bone affect

const int MAX_JOINTS = 150;
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
	mat4 boneTransform = jointTransforms[in_jointIndices[0]]*in_weights[0];
	boneTransform += jointTransforms[in_jointIndices[1]]*in_weights[1];
	boneTransform += jointTransforms[in_jointIndices[2]]*in_weights[2];

	vec4 posL = boneTransform * vec4(aPos, 1.0);
	gl_Position = projection * view * model * posL;
	TexCoords = aTexCoords;

	vec4 normalL = boneTransform * vec4(aNormal, 0.0);
	Normal = (transpose(inverse(model)) * normalL).xyz;
	FragPos = (model * posL).xyz;
}