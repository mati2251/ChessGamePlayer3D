#version 330 core

layout(location = 0) in vec4 vertex;
layout(location = 1) in vec4 color;

out vec4 fragmentColor;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

void main() {
    gl_Position = P * V * M * vertex;
    fragmentColor = color;
}
