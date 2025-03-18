#include "GameObject.h"
#include <glm/gtc/matrix_transform.hpp>

GameObject::GameObject(Mesh* mesh, const glm::vec3& position)
    : mesh(mesh), model(nullptr), position(position), rotation(0.0f), scale(1.0f) {}

GameObject::GameObject(Model* model, const glm::vec3& position)
    : model(model), mesh(nullptr), position(position), rotation(0.0f), scale(1.0f) {}

void GameObject::setPosition(const glm::vec3& position) {
    this->position = position;
}

void GameObject::setRotation(const glm::vec3& rotation) {
    this->rotation = rotation;
}

void GameObject::setScale(const glm::vec3& scale) {
    this->scale = scale;
}

glm::vec3 GameObject::getPosition() const {
    return position;
}

glm::vec3 GameObject::getRotation() const {
    return rotation;
}

glm::vec3 GameObject::getScale() const {
    return scale;
}

void GameObject::update(float deltaTime) {
    // Placeholder for update logic (physics, movement, etc.)
}

void GameObject::render(const Shader& shader) const {
    // Calculate the model matrix
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::scale(modelMatrix, scale);

    // Render either Mesh or Model
    if (mesh) {
        shader.use();
        mesh->draw();  // Assuming Mesh has a draw function
    }
    else if (model) {
        shader.use();
        //model->draw(shader); // Assuming Model has a draw function
    }
}
