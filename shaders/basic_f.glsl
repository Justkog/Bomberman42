#version 330 core

out vec4 outColor;

uniform vec4 color;

in vec3 vNormal;

void main()
{
    vec3 lightDir = normalize(vec3(-1, -0.75f, -0.5f));
    float l = max(dot(vNormal, lightDir), 0.05f);
    outColor = color * vec4(l, l, l, 1.0f);
}