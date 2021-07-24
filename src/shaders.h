constexpr const char* VERTEX_SHADER_SOURCE = R"(#version 330 core

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
)";
constexpr const char* FRAGMENT_SHADER_SOURCE = R"(#version 330 core

in vec2 uv;
in float fragmentTime;

out vec3 color;

uniform sampler2D u_texture;

void main()
{
    color = texture(u_texture, uv).rgb;
}
)";