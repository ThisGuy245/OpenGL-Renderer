#include "GameObject.h"
#include "Model.h"  // Include Model, Shader, Texture
#include "Shader.h"
#include "Texture.h"

GameObject::GameObject(Model* model, Shader* shader, Texture* texture)
    : model(model), shader(shader), texture(texture) {
    transform = Transform();  // Default Transform
}

void GameObject::Update() {
    // Apply transformations here
}

void GameObject::Draw(Renderer& renderer) {
    texture->bind();
    shader->use();
    model->Draw();
    texture->unbind();
}
