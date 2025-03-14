// VertexBuffer.cpp
#include "VertexBuffer.h"
#include <iostream>

VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &m_vboID);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_vboID);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::uploadData(const std::vector<float>& data, GLenum usage) {
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), usage);
}