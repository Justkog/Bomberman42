#version 330 core

out vec4 outColor;

uniform vec4 color;
uniform sampler2D albedo;

in vec3 vNormal;
in vec2 vTexture;

void main()
{
    vec3 lightDir = normalize(vec3(-1, -0.75f, -0.5f));
    float l = max(dot(vNormal, lightDir), 0.15f);
    vec4 texColor = texture(albedo, vTexture);
    outColor = (color * texColor) * vec4(l, l, l, 1.0f);
}