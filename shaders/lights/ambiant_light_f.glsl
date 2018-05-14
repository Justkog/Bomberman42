#version 400 core

#include "light.glsl"

out vec4 outColor;

uniform vec4 color;
uniform sampler2D albedo;
uniform int hasAlbedo;
uniform sampler2D normal;
uniform int hasNormal;
uniform sampler2D bump;
uniform int hasBump;

in vec3 vNormal;
in vec2 vTexture;
in mat3 TBN;
in vec3 vTangentViewPos;
in vec3 vTangentFragPos;
in vec4 vWeight;

uniform Light light;

void main()
{
    vec3 lightDir = normalize(vec3(0, -1, 0.5));

    vec2 texCoords;
    if (hasBump == 1)
    {
        vec3 viewDir = normalize(vTangentViewPos - vTangentFragPos);
        vec2 texCoords = ParallaxMapping(bump, vTexture, viewDir);
        // if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
        //     discard;
    }
    else
    {
        texCoords = vTexture;
    }

    vec3 tNormal;
    if (hasNormal == 1)
    {
        tNormal = texture(normal, texCoords).rgb;
        tNormal = normalize(tNormal * 2.0 - 1.0);
        tNormal = normalize(TBN * tNormal);
    }
    else
    {
        tNormal = vNormal;
    }

    vec4 lightIntensity = light.color * light.intensity;
    if (hasAlbedo == 1)
    {
        vec4 texColor = texture(albedo, texCoords);
        outColor = color * texColor * lightIntensity;
    }
    else
    {
        outColor = color * light.color * lightIntensity;
    }
    float roughtness = 4;

    vec3 reflection = reflect(-normalize(fragPos - viewPosition), tNormal);
    vec3 env = textureLod(envMap, reflection, roughtness).rgb;


    float fresnel = calcFresnel(viewPosition, tNormal, 1) * 0.4;
    vec3 fresnelReflection = mix(outColor.rgb, env * 0.5, fresnel);
    outColor = vec4(fresnelReflection, 1.0);
}