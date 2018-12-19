#version 330 core

out vec4 FragColor;

in vec3 ourColor;  
in vec2 TexCoord;

uniform sampler2D texture1; // OpenGL built-in, it's 0 => GL_TEXTURE_0
uniform sampler2D texture2; // OpenGL built-in, it's 1 => GL_TEXTURE_1

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.7); // buit-in too, first arg is the sampler, the second is the coordinates
    //FragColor = texture(texture2, TexCoord); // buit-in too, first arg is the sampler, the second is the coordinates
    										 // the colors of the text are found beacause we bind the texture
    // The output of this fragment shader is then the (filtered) color of the texture at the (interpolated) texture coordinate
}