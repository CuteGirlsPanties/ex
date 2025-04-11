#pragma once

#include <glad/gles2.h>

#include <vector>

struct Vertex {
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;
};

struct UV {
    GLfloat x;
    GLfloat y;
};

class Mesh {
public:
    Mesh(std::vector<Vertex> vertices, std::vector<UV> uvs);
    ~Mesh();

    void bind() const;
    virtual void draw();

private:
    GLuint m_vao;
    GLuint m_buffers[2];
    GLsizei m_vertexCount;
};

class TileMesh : public Mesh {
public:
    TileMesh();
};
