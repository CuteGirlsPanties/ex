#version 300 es

precision highp float;

uniform usampler2D map_tile;

in vec2 uv;

out vec4 output0;

void main() {
    uvec4 id = texture(map_tile, uv);
    output0 = vec4(uv, 0.0, 1.0);
}
