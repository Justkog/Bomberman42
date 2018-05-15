#version 400 core
layout(location = 0) in vec3 vertexPosition;
layout(location = 2) in vec2 vertexTexture;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 vTexture;

void main()
{
    gl_Position = vec4(vertexPosition, 1);

    vTexture = vec2(1.0 - vertexTexture.y, vertexTexture.x);
}