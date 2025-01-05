#version 330 core

in vec3 vTexCoords;

out vec4 fFragColor;

uniform samplerCube uTexture;


void main()
{
    fFragColor = texture(uTexture, vTexCoords);
}
