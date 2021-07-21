#version 330 core

in vec3 fragmentColor;
in float fragmentTime;

out vec3 color;

void main()
{
    color = vec3(fragmentColor.x + abs(sin(fragmentTime)) / 10,
                 fragmentColor.y + abs(cos(fragmentTime)) / 10,
                 cos(fragmentTime));
}