#version 420

in vec2 texCoord;

out vec4 fragColor;

uniform bool solidColor; // we don't use this because this is set by Mesh (spaghetti code ikr)

uniform bool useTexture;
uniform sampler2D tex;
uniform vec3 color;

void main() {
    if (useTexture) {
        fragColor = texture(tex, texCoord) * vec4(color, 1.0);
    }
    else {
        fragColor = vec4(color, 1.0);
    }

    if (fragColor.a < 0.1) {
        discard;
    }
}