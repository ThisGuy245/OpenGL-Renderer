#include "GameObject.h"
#include "Mesh.h"  // Include Mesh, Shader, Texture
#include "Shader.h"
#include "Texture.h"

GameObject::GameObject(Mesh* mesh, Shader* shader, Texture* texture)
    : mesh(mesh), shader(shader), texture(texture) {
    transform = Transform();  // Default Transform
}

void GameObject::Update(float deltaTime) {
    // Apply transformations here
}

void GameObject::Draw(Renderer& renderer) {
    shader->use();
    texture->bind();
    mesh->draw();
}
