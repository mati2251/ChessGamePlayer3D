#version 330 core


in vec4 fragmentColor;
out vec4 pixelColor;

uniform vec3 center;
uniform float radius;

void main() {
    pixelColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
