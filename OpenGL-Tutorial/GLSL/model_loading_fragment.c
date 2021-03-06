#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform bool transparent;

void main()
{    
    FragColor = texture(texture_diffuse1, TexCoords);
    if (transparent) {
	    FragColor.a = 0.5;
    }
}