#version 420

in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D tex;
uniform bool solidColor;
uniform vec3 color;

void main() {
    fragColor = texture(tex, texCoord);
    if (fragColor.a < 0.1) {
        discard;
    }
}