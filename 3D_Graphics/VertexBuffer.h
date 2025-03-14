// VertexBuffer.h
#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <GL/glew.h>
#include <vector>

class VertexBuffer {
private:
    GLuint m_vboID;
public:
    VertexBuffer();
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
    void uploadData(const std::vector<float>& data, GLenum usage);
};

#endif // VERTEXBUFFER_H