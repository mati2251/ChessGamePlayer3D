#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;



layout (location=0) in vec3 vertex;
layout (location=1) in vec3 normal;
layout (location=2) in vec2 texCoord;

out vec4 l;
out vec4 n;
out vec4 v;

out vec2 iTexCoord0;
out vec3 pos;

void main(void) {
    vec4 ver = vec4(vertex, 1.0);
    gl_Position=P*V*M*ver;
    vec4 lp = vec4(2, 2, -6, 1);
    l = normalize(V * lp - V*M*ver);
    v = normalize(vec4(0, 0, 0, 1) - V * M * ver);
    n = normalize(V * M * vec4(normal,0));
    pos = vec3(M * vec4(vertex, 1.0));
    iTexCoord0=texCoord;
}
