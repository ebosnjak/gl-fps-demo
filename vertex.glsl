#version 420

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;
layout (location = 2) in vec2 uv;

out vec3 fragPos;
out vec3 fragScreenPos;
out vec3 normal;
out vec2 texCoord;

uniform bool isViewmodel;
uniform vec3 cameraPos;

uniform mat4 playerModel;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    gl_Position = proj * (isViewmodel ? mat4(1.0) : view) * model * vec4(pos, 1.0);
    texCoord = uv;
    normal = norm;
    fragPos = ((isViewmodel ? playerModel : mat4(1.0)) * model * vec4(pos, 1.0)).xyz;

    fragScreenPos = gl_Position.xyz;
}