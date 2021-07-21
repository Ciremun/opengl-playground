#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;

uniform mat4 MVP;
uniform float time;

out vec3 fragmentColor;
out float fragmentTime;

void main()
{
    gl_Position = MVP * vec4(vertexPosition, 1);
    fragmentColor = vertexColor;
    fragmentTime = time;
}
