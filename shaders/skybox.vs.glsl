#version 330 core

layout(location = 0) in vec3 aVertexPosition;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;

out vec3 vTexCoords;

void main()
{
    vTexCoords = aVertexPosition;
    vec4 pos = uMVPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);
    gl_Position = pos.xyww;
}
