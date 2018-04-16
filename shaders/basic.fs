#version 330 core

out vec4 outColor;

uniform vec3 lightDir;
uniform vec3 color;

in vec3 vNormal;

void main()
{
    float l = max(dot(vNormal, lightDir), 0.05f);
    outColor = vec4(color * l, 1.0);
}