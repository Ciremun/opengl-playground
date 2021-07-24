#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;

uniform mat4 MVP;
uniform float time;

out vec2 uv;
out float fragmentTime;

void main()
{
    gl_Position = MVP * vec4(vertexPosition, 1);
    uv = vertexUV.xy;
    fragmentTime = time;
}
