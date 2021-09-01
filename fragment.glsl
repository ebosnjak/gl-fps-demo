#version 420

in vec3 normal;
in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D tex;

void main() {
    fragColor = texture(tex, texCoord);
}