#version 330 core
out vec4 color;

uniform sampler2D sprite;

in vec2 vTexture;
in vec4 vColor;

void main()
{
    color = (texture(sprite, vTexture) * vColor) * 0.3;
} 