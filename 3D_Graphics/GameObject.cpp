// GameObject.cpp
#include "GameObject.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"


GameObject::GameObject(Mesh* mesh, Shader* shader, Texture* texture)
    : mesh(mesh), shader(shader), texture(texture) {
    transform = Transform();  // Default Transform
}

void GameObject::Update(float deltaTime) {
    // You can apply transformations here, for example:
    // - Moving the object
    // - Rotating the object
    // - Scaling the object
    // For now, it's just an empty function to keep it ready for further modifications.
}

void GameObject::Draw(Renderer& renderer) {
    // Bind the shader and texture before drawing the mesh
    shader->use();
    texture->bind();

    // Pass the transform to the shader for model matrix calculations
    // Usually, this can be done using the shader's `setUniform` function:
    shader->setMat4("model", transform.GetModelMatrix());

    // Draw the mesh with the shader and texture
    mesh->draw();
}
