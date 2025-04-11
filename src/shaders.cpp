#include "shaders.hpp"

#include <cstdio>
#include <string>

static GLuint createShader(std::string name, GLenum type, const GLchar* src, GLint len) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, &len);
    glCompileShader(shader);

    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success != GL_TRUE) {
        static GLchar buf[10240];
        static GLsizei len;
        glGetShaderInfoLog(shader, sizeof(buf), &len, buf);
        buf[len] = '\0';
        printf("Shader error (%s): %s\n", name.c_str(), buf);
        return 0;
    }

    return shader;
}

static GLuint createProgram(std::string name, GLuint vert, GLuint frag) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);

    GLint success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (success != GL_TRUE) {
        static GLchar buf[10240];
        static GLsizei len;
        glGetProgramInfoLog(program, sizeof(buf), &len, buf);
        buf[len] = '\0';
        printf("Program error (%s): %s\n", name.c_str(), buf);
        return 0;
    }

    return program;
}

static const char* shader_src_tile_vert = R"~~(#version 300 es

layout(location = 0) in vec4 POS;
layout(location = 1) in vec2 UV;

uniform mat4 pvMatrix;
uniform mat4 modelMatrix;

out vec2 uv;

void main() {
    gl_Position = pvMatrix * modelMatrix * POS;
    uv = UV;
}
)~~";
static GLuint shader_tile_vert = 0;
static const char* shader_src_map_tile_frag = R"~~(#version 300 es

precision highp float;

uniform usampler2D map_tile;

in vec2 uv;

out vec4 output0;

void main() {
    uvec4 id = texture(map_tile, uv);
    output0 = vec4(uv, 0.0, 1.0);
}
)~~";
static GLuint shader_map_tile_frag = 0;
static GLuint program_mapTile = 0;
void mapTileShader::bind() {
    glUseProgram(program_mapTile);
}
static GLuint uniforms_mapTile[3];
void mapTileShader::pvMatrix(GLfloat m[4][4]) {
    glUniformMatrix4fv(uniforms_mapTile[0], 1, false, &m[0][0]);
}
void mapTileShader::modelMatrix(GLfloat m[4][4]) {
    glUniformMatrix4fv(uniforms_mapTile[1], 1, false, &m[0][0]);
}
void mapTileShader::map_tile(GLuint textureSlot) {
    glUniform1i(uniforms_mapTile[2], textureSlot);
}
void initShaders() {
    shader_tile_vert = createShader("tile.vert", GL_VERTEX_SHADER, shader_src_tile_vert, 226);
    shader_map_tile_frag = createShader("map_tile.frag", GL_FRAGMENT_SHADER, shader_src_map_tile_frag, 191);
    program_mapTile = createProgram("mapTile", shader_tile_vert, shader_map_tile_frag);
    uniforms_mapTile[0] = glGetUniformLocation(program_mapTile, "pvMatrix");
    uniforms_mapTile[1] = glGetUniformLocation(program_mapTile, "modelMatrix");
    uniforms_mapTile[2] = glGetUniformLocation(program_mapTile, "map_tile");
}
