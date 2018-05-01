#version 330 core
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexture;
layout(location = 3) in vec3 vertexTangent;
layout(location = 4) in vec3 vertexBitangent;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 viewPos;
uniform vec3 viewDir;

out vec3 vNormal;
out vec2 vTexture;
out mat3 TBN;
out vec3 vTangentViewPos;
out vec3 vTangentFragPos;

void main()
{
    gl_Position = projection * view * model * vec4(vertexPosition, 1);
    vec3 fragPos = vec3(model * vec4(vertexPosition, 1));

    vec3 T = normalize(vec3(model * vec4(vertexTangent, 0.0)));
    vec3 B = normalize(vec3(model * vec4(vertexBitangent, 0.0)));
    vNormal = normalize(vec3(model * vec4(vertexNormal, 0)));
    TBN = mat3(T, B, vNormal);

    vTangentViewPos = TBN * viewPos;
    vTangentFragPos = TBN * fragPos;

    vTexture = vertexTexture * vec2(1, -1);
}