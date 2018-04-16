#version 330 core
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 vNormal;

void main()
{
    gl_Position = projection * view * model * vec4(vertexPosition, 1);
    vNormal = (view * model * vec4(vertexNormal, 0)).xyz;
}