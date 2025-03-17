#include "Primitives.h"

#include <glm/glm.hpp>

#include <vector>

#include "Mesh.h"

constexpr float pi = 3.14159265358979323846f;

Mesh Primitives::CreateCube(float size, const Texture& defaultTexture) {

    std::vector<Vertex> vertices = {

        // Front face

        { { -size, -size,  size }, { 0.0f, 0.0f } },

        { {  size, -size,  size }, { 1.0f, 0.0f } },

        { {  size,  size,  size }, { 1.0f, 1.0f } },

        { { -size,  size,  size }, { 0.0f, 1.0f } },

        // Back face

        { { -size, -size, -size }, { 1.0f, 0.0f } },

        { {  size, -size, -size }, { 0.0f, 0.0f } },

        { {  size,  size, -size }, { 0.0f, 1.0f } },

        { { -size,  size, -size }, { 1.0f, 1.0f } }

    };

    std::vector<unsigned int> indices = {

    0, 1, 2, 2, 3, 0,

    4, 5, 6, 6, 7, 4,

    4, 0, 3, 3, 7, 4,

    1, 5, 6, 6, 2, 1,

    3, 2, 6, 6, 7, 3,

    4, 5, 1, 1, 0, 4

    };

    return Mesh(vertices, indices, defaultTexture); // Fixed 'texture' to 'defaultTexture'

}

Mesh Primitives::CreateSphere(float radius, int segments, const Texture& defaultTexture) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i <= segments; ++i) {
        float lat = static_cast<float>(i) / segments * pi;
        for (int j = 0; j <= segments; ++j) {
            float lon = static_cast<float>(j) / segments * 2.0f * pi;

            Vertex vertex;
            vertex.position = {
                radius * sin(lat) * cos(lon),
                radius * cos(lat),
                radius * sin(lat) * sin(lon)
            };
            vertex.texCoords = {
                static_cast<float>(j) / segments,
                static_cast<float>(i) / segments
            };
            vertices.push_back(vertex);
        }
    }

    for (int i = 0; i < segments; ++i) {
        for (int j = 0; j < segments; ++j) {
            int first = i * (segments + 1) + j;
            int second = first + segments + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }

    return Mesh(vertices, indices, defaultTexture);
}

Mesh Primitives::CreatePlane(float width, float height, const Texture& defaultTexture) {
    // Define the 4 vertices of the plane
    std::vector<Vertex> vertices = {
        { { -width / 2, 0.0f, -height / 2 }, { 0.0f, 0.0f } }, // Bottom-left
        { {  width / 2, 0.0f, -height / 2 }, { 1.0f, 0.0f } }, // Bottom-right
        { {  width / 2, 0.0f,  height / 2 }, { 1.0f, 1.0f } }, // Top-right
        { { -width / 2, 0.0f,  height / 2 }, { 0.0f, 1.0f } }  // Top-left
    };

    // Define the indices for the 2 triangles
    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0
    };

    return Mesh(vertices, indices, defaultTexture);
}