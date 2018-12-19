#version 330 core
layout (location = 0) in vec3 aPos; //postion variable has an attribute position 0
layout (location = 1) in vec3 aColor; // color variable has an attribute position 1
layout (location = 2) in vec2 aTexCoord; // text coordinates

uniform mat4 transform; // We take the transformation matrix trough uniform


out vec3 ourColor;
out vec2 TexCoord; // We forward it to the fragment shader

void main() {
	gl_Position = transform * vec4(aPos, 1.0); // We apply the transformation matrice
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}