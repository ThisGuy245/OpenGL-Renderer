#include "Primitives.h"
#include <glm/glm.hpp>
#include <vector>
#include "Mesh.h"

constexpr float pi = 3.14159265358979323846f;

// Cube
Mesh Primitives::CreateCube(float size) {
    std::vector<Vertex> vertices = {
        // Front face
        Vertex({ -size, -size,  size }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }),
        Vertex({  size, -size,  size }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }),
        Vertex({  size,  size,  size }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }),
        Vertex({ -size,  size,  size }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }),
        // Back face
        Vertex({ -size, -size, -size }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }),
        Vertex({  size, -size, -size }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }),
        Vertex({  size,  size, -size }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }),
        Vertex({ -size,  size, -size }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f })
    };

    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        4, 0, 3, 3, 7, 4,
        1, 5, 6, 6, 2, 1,
        3, 2, 6, 6, 7, 3,
        4, 5, 1, 1, 0, 4
    };

    return Mesh(vertices, indices); // No texture, only vertices and indices
}


// Sphere
Mesh Primitives::CreateSphere(float radius, int segments) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i <= segments; ++i) {
        float lat = static_cast<float>(i) / segments * pi;
        for (int j = 0; j <= segments; ++j) {
            float lon = static_cast<float>(j) / segments * 2.0f * pi;

            // Use the Vertex constructor to initialize position, normal, and texCoords
            Vertex vertex(
                { radius * sin(lat) * cos(lon), radius * cos(lat), radius * sin(lat) * sin(lon) }, // position
                { radius * sin(lat) * cos(lon), radius * cos(lat), radius * sin(lat) * sin(lon) }, // normal
                { static_cast<float>(j) / segments, static_cast<float>(i) / segments }            // texCoords
            );

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

    return Mesh(vertices, indices); // No Texture, only vertices and indices
}



// Plane
Mesh Primitives::CreatePlane(float width, float height) {
    std::vector<Vertex> vertices = {
        // Positions                          // Normals                  // Texture Coordinates
        Vertex({ -width / 2, 0.0f, -height / 2 }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f }),
        Vertex({  width / 2, 0.0f, -height / 2 }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f }),
        Vertex({  width / 2, 0.0f,  height / 2 }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f }),
        Vertex({ -width / 2, 0.0f,  height / 2 }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f })
    };

    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0
    };

    return Mesh(vertices, indices); // No Texture, only vertices and indices
}

