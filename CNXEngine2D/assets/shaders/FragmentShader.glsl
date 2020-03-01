#version 460 core

layout(location = 0) out vec4 fragmentColor;

uniform vec4 vertexColor;

void main()
{
    fragmentColor = vertexColor;
};
