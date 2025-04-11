#include "mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<UV> uvs) {
    m_vertexCount = vertices.size();
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    glGenBuffers(2, m_buffers);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(UV), uvs.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(UV), (void*)0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}

Mesh::~Mesh() {
}

void Mesh::bind() const {
    glBindVertexArray(m_vao);
}

void Mesh::draw() {
    glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
}

static const std::vector<Vertex> tileVertices = {
    { 0.0, 0.0, 0.0, 1.0 },
    { 1.0, 0.0, 0.0, 1.0 },
    { 1.0, 1.0, 0.0, 1.0 },
    { 0.0, 0.0, 0.0, 1.0 },
    { 1.0, 1.0, 0.0, 1.0 },
    { 0.0, 1.0, 0.0, 1.0 },
};
static const std::vector<UV> tileUvs = {
    { 0.0, 1.0 },
    { 1.0, 1.0 },
    { 1.0, 0.0 },
    { 0.0, 1.0 },
    { 1.0, 0.0 },
    { 0.0, 0.0 },
};

TileMesh::TileMesh()
    : Mesh(tileVertices, tileUvs) {
}
