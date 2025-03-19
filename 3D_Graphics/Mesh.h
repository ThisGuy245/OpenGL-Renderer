#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <vector>
#include "Texture.h"
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;  // Added for future lighting support
    glm::vec2 texCoords;
};

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices,
        const std::vector<unsigned int>& indices,
        Texture texture); // Pass texture by value
    ~Mesh();

    void draw() const;
    void bind() const;  // Added for explicit VAO binding
    void unbind() const; // Added for explicit VAO unbinding

private:
    GLuint vao, vbo, ebo;
    Texture texture; // Store texture as a value instead of a reference
    size_t indexCount;
};

#endif // MESH_H