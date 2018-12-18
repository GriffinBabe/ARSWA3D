#version 330 core

out vec4 FragColor;

in vec3 ourColor;  
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord) 
    // The output of this fragment shader is then the (filtered) color of the texture at the (interpolated) texture coordinate
}