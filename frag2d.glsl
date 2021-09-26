#version 420

in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D tex;
uniform bool solidColor;
uniform vec3 color;

void main() {
    fragColor = texture(tex, texCoord) * vec4(color, 1.0);
    if (fragColor.a < 0.1) {
        discard;
    }
}