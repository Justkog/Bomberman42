#version 330 core
#define MAX_BONES 25

layout(location = 0) in vec3 vertexPosition;
layout(location = 5) in ivec4 vertexBoneIDs;
layout(location = 6) in vec4 vertexWeights;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform mat4 bonesTransforms[MAX_BONES];
uniform int hasBones;

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
}