#pragma once

#include <glad/gles2.h>

struct mapTileShader {
    static void bind();
    static void pvMatrix(GLfloat m[4][4]);
    static void modelMatrix(GLfloat m[4][4]);
    static void map_tile(GLuint textureSlot);
};

void initShaders();
