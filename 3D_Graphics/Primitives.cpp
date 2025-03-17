#include "Primitives.h"


Mesh Primitives::CreateCube(float size) {
	// Definé les vertice et indices pour un cube
	std::vector<Vertex> vertices = {/* vertice de cube */ };
	std::vector<unsigned int> indices = {/* indices de cube */};
	Texture defaultTexture("path/to/default_texture.png");
	return Mesh(vertices, indices, defaultTexture);
}

Mesh Primitives::CreateSphere(float radius, int segments) {
    // Generate sphere vertices and indices
    std::vector<Vertex> vertices = { /* sphere vertices */ };
    std::vector<unsigned int> indices = { /* sphere indices */ };
    Texture defaultTexture("path/to/default_texture.png");
    return Mesh(vertices, indices, defaultTexture);
}

Mesh Primitives::CreatePlane(float width, float height) {
    // Generate plane vertices and indices
    std::vector<Vertex> vertices = { /* plane vertices */ };
    std::vector<unsigned int> indices = { /* plane indices */ };
    Texture defaultTexture("path/to/default_texture.png");
    return Mesh(vertices, indices, defaultTexture);
}