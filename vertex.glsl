#version 420

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    gl_Position = proj * view * model * vec4(pos, 1.0);
    texCoord = uv;
}