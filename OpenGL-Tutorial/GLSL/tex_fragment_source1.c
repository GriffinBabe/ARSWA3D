#version 330 core

out vec4 FragColor;

in vec3 ourColor;  
in vec2 TexCoord;

uniform sampler2D texture1; // OpenGL built-in

void main()
{
    FragColor = texture(texture1, TexCoord); // buit-in too, first arg is the sampler, the second is the coordinates
    										 // the colors of the text are found beacause we bind the texture
    // The output of this fragment shader is then the (filtered) color of the texture at the (interpolated) texture coordinate
}