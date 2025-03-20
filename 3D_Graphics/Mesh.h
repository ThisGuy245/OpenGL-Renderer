#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;

    // Constructor to initialize all fields
    Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 tex)
        : position(pos), normal(norm), texCoords(tex) {}
};


class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    // Move Constructor & Move Assignment (for efficient resource handling)
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;

    void draw() const;
    void bind() const;
    void unbind() const;
    size_t getIndexCount() const { return indexCount; }

private:
    GLuint vao, vbo, ebo;
    size_t indexCount;

    void setupMesh();
};

#endif // MESH_H
