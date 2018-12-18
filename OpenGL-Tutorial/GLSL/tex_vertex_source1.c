#version 330 core
layout (location = 0) in vec3 aPos; //postion variable has an attribute position 0
layout (location = 1) in vec3 aColor; // color variable has an attribute position 1
layout (location = 2) in vec2 aTexCoord; // text coordinates

uniform float offset;

out vec3 ourColor;
out vec2 TexCoord; // We forward it to the fragment shader

void main() {
	gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
	TexCoord = aTexCoord;
}