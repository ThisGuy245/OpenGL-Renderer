// VertexArray.h
#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <GL/glew.h>

class VertexArray {
private:
    GLuint m_vaoID;
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;
};

#endif // VERTEXARRAY_H