constexpr const char* VERTEX_SHADER_SOURCE = R"(#version 330 core

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
)";
constexpr const char* FRAGMENT_SHADER_SOURCE = R"(#version 330 core

in vec3 fragmentColor;
in float fragmentTime;

out vec3 color;

void main()
{
    color = vec3(fragmentColor.x + abs(sin(fragmentTime)) / 10,
                 fragmentColor.y + abs(cos(fragmentTime)) / 10,
                 cos(fragmentTime));
})";