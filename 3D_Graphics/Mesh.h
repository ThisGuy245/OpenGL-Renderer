#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <vector>
#include "Texture.h"
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoords;
};


class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Texture& texture);
    ~Mesh();

    void draw() const;

private:
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    Texture& texture;
    size_t indexCount;
};

#endif // MESH_H