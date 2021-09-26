#version 420

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;
layout (location = 2) in vec2 uv;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 proj;

void main() {
    gl_Position = proj * model * vec4(pos, 1.0);
    texCoord = uv;
}