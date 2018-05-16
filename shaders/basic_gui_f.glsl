#version 400 core

out vec4 outColor;

uniform sampler2D albedo;

in vec2 vTexture;

void main()
{
	outColor = texture(albedo, vTexture);
}