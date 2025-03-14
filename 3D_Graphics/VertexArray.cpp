// VertexArray.cpp
#include "VertexArray.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_vaoID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_vaoID);
}

void VertexArray::bind() const {
    glBindVertexArray(m_vaoID);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}
