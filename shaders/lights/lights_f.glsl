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
uniform sampler2D rougth;
uniform int hasRougth;
uniform float rougthFactor;
uniform sampler2D metalic;
uniform int hasMetalic;
uniform float metalicFactor;

uniform int hasDirectionalLight;

in vec3 vNormal;
in vec2 vTexture;
in mat3 TBN;
in vec3 vTangentViewPos;
in vec3 vTangentFragPos;
in vec4 vWeight;
in vec4 lightPosition;

uniform Light light;
uniform DirectionalLight directionalLight;

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

    float finalRoughtness = rougthFactor;
    float finalMetalic = metalicFactor;

    if (hasRougth == 1)
        finalRoughtness = texture(rougth, texCoords).r;
    if (hasMetalic == 1)
        finalMetalic = texture(metalic, texCoords).r;

    specular_power = 100 - finalRoughtness * 100 + finalMetalic;
    specular_intensity = 2 - finalRoughtness * 2 + finalMetalic;

    vec4 dirLight = vec4(0, 0, 0, 0);
    if (hasDirectionalLight == 1)
        dirLight = calcDirectionalLight(directionalLight, tNormal) * calcBlurredShadow(lightPosition, 2);
    vec4 lightIntensity = light.color * light.intensity + dirLight;
    if (hasAlbedo == 1)
    {
        vec4 texColor = texture(albedo, texCoords);
        outColor = color * texColor * lightIntensity;
    }
    else
    {
        outColor = color * light.color * lightIntensity;
    }

    vec4 pbr = calcPBR(outColor, tNormal, finalRoughtness, finalMetalic);
    outColor = vec4(pbr.rgb, 1.0);
}