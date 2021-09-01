#version 420

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

out vec4 fragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform sampler2D tex;
uniform Material material;
uniform vec3 cameraPos;

void main() {
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 lightPos = vec3(3.0, 2.0, 4.0);

    vec3 ambient = 0.2 * lightColor * material.ambient;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 diffuse = 0.5 * lightColor * (max(0.0, dot(norm, lightDir)) * material.diffuse);

    // add specular
    vec3 ref = reflect(-lightDir, norm);
    float specFactor = pow(max(0.0, dot(ref, normalize(cameraPos - fragPos))), material.shininess);
    vec3 specular = 1.0 * lightColor * (specFactor * material.specular);

    vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result, 1.0);
}