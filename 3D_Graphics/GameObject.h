// GameObject.h
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glm/glm.hpp>
#include <string>
#include "Renderer.h"
#include "Transform.h"

class Mesh;
class Texture;
class Shader;

// GameObject.h
class GameObject {
public:
    GameObject(Mesh* mesh, Shader* shader, Texture* texture)
        : mesh(mesh), shader(shader), texture(texture) {
        transform = Transform();  // Default Transform
    }

    void Update(float deltaTime) {
        // You can apply transformations here
    }

    void Draw(Renderer& renderer) {
        // Bind the shader and texture before drawing the mesh
        shader->use();
        texture->bind();
        mesh->draw();
    }

    Transform transform;  // Stores position, rotation, scale
private:
    Mesh* mesh;
    Shader* shader;
    Texture* texture;
};

#endif