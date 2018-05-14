#version 330 core
#define MAX_BONES 120

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexture;
layout(location = 3) in vec3 vertexTangent;
layout(location = 4) in vec3 vertexBitangent;
layout(location = 5) in ivec4 vertexBoneIDs;
layout(location = 6) in vec4 vertexWeights;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform mat4 bonesTransforms[MAX_BONES];
uniform int hasBones;

uniform vec3 viewPos;
uniform vec3 viewDir;

out vec3 vNormal;
out vec2 vTexture;
out mat3 TBN;
out vec3 vTangentViewPos;
out vec3 vTangentFragPos;
out vec3 viewPosition;
out vec3 viewDirection;
out vec3 fragPos;

void main()
{
    mat4 boneTransform = mat4(1.0);

    if (hasBones == 1)
    {
        boneTransform = bonesTransforms[vertexBoneIDs[0]] * vertexWeights[0];
        boneTransform += bonesTransforms[vertexBoneIDs[1]] * vertexWeights[1];
        boneTransform += bonesTransforms[vertexBoneIDs[2]] * vertexWeights[2];
        boneTransform += bonesTransforms[vertexBoneIDs[3]] * vertexWeights[3];
    }

    gl_Position = projection * view * model * boneTransform * vec4(vertexPosition, 1);
    fragPos = vec3(model * vec4(vertexPosition, 1));

    vec3 T = normalize(vec3(model * boneTransform * vec4(vertexTangent, 0.0)));
    vec3 B = normalize(vec3(model * boneTransform * vec4(vertexBitangent, 0.0)));
    vNormal = normalize(vec3(model * boneTransform * vec4(vertexNormal, 0)));
    TBN = mat3(T, B, vNormal);

    vTangentViewPos = TBN * viewPos;
    vTangentFragPos = TBN * fragPos;

    vTexture = vertexTexture * vec2(1, -1);
    viewPosition = viewPos;
    viewDirection = viewDir;
}