#version 330 core

in vec2 uv;
in float fragmentTime;

out vec3 color;

uniform sampler2D u_texture;

void main()
{
    vec3 tex = texture(u_texture, uv).rgb;
    vec3 effect = vec3(1.0, 1.0, 1.0) / abs(sin(fragmentTime)) / 2.0;
    color = tex * effect;
}
