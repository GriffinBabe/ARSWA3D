#version 330 core
layout (location = 0) in vec3 aPos; //postion variable has an attribute position 0
layout (location = 1) in vec2 aTexCoord; // text coordinates

uniform mat4 model; // We take the transformation matrix trough uniform
uniform mat4 view; // We take the transformation matrix trough uniform
uniform mat4 projection; // We take the transformation matrix trough uniform


out vec2 TexCoord; // We forward it to the fragment shader

void main() {
	gl_Position = projection * view * model * vec4(aPos, 1.0); // We apply the transformation matrice
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}