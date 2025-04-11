#version 300 es

layout(location = 0) in vec4 POS;
layout(location = 1) in vec2 UV;

uniform mat4 pvMatrix;
uniform mat4 modelMatrix;

out vec2 uv;

void main() {
    gl_Position = pvMatrix * modelMatrix * POS;
    uv = UV;
}
