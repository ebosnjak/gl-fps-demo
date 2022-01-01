#version 420

in vec3 fragPos;
in vec3 fragScreenPos;
in vec3 normal;
in vec2 texCoord;

out vec4 fragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;

    bool useDiffMap, useBumpMap, useSpecMap;
    sampler2D diffuseMap, bumpMap, specularMap;
};

struct Light {
    vec4 vector;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform sampler2D noiseTex;
uniform vec2 noiseResolution;

uniform bool solidColor;
uniform vec3 color;
uniform Material material;

uniform Light light;

uniform vec3 cameraPos;

uniform bool isViewmodel;

void main() {
    if (solidColor) {
        fragColor = vec4(color, 1.0);
        return;
    }

    vec3 lightDir = -normalize(light.vector.xyz);       // for directional lights, vector.xyz is their direction and w is 0.0
    if (light.vector.w == 1.0) {            // for point lights, vector.xyz is their position and w is 1.0
        lightDir = normalize(light.vector.xyz - fragPos);
    }

    vec3 diff = vec3(1.0, 1.0, 1.0);
    if (material.useDiffMap) {
        diff = texture(material.diffuseMap, texCoord).xyz;
    }

    vec3 ambient = light.ambient * material.ambient * diff;

    vec3 norm = normalize(normal);
    vec3 diffuse = light.diffuse * (max(0.0, dot(norm, lightDir)) * material.diffuse * diff);

    vec3 ref = reflect(-lightDir, norm);
    float specFactor = pow(max(0.0, dot(ref, normalize(cameraPos - fragPos))), material.shininess);
    vec3 spec = vec3(1.0, 1.0, 1.0);
    if (material.useSpecMap) {
        spec = texture(material.specularMap, texCoord).xyz;
    }
    vec3 specular = light.specular * (specFactor * material.specular * spec);

    float noise = texture(noiseTex, fragScreenPos.xy + vec2(1.0, 1.0)).x;

    vec3 result = ambient + diffuse + specular + mix(-0.5 / 255.0, 0.5 / 255.0, noise);
    fragColor = vec4(result, 1.0);
}