#version 330 core

in vec2 uv;
in float fragmentTime;

out vec3 color;

uniform sampler2D u_texture;

void main()
{
    color = texture(u_texture, uv).rgb;
}
