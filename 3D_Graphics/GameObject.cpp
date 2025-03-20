#include "GameObject.h"

GameObject::GameObject(const std::string& modelPath, GameObjectType type, const std::string& texturePath)
    : m_type(type), m_position(0.0f, 0.0f, 0.0f), m_rotation(0.0f, 0.0f, 0.0f), m_scale(1.0f, 1.0f, 1.0f) {

    if (m_type == GameObjectType::Model) {
        m_model = std::make_unique<Model>(modelPath);
        m_texture = std::make_shared<Texture>(texturePath, TextureType::DIFFUSE);
    }
    // Add logic for handling other types of GameObjects (like Primitive, Camera, Empty)
}

void GameObject::Render(Shader& shader) {
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    // Apply transformations (translation, rotation, scale)
    modelMatrix = glm::translate(modelMatrix, m_position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::scale(modelMatrix, m_scale);

    // Set the model matrix in the shader
    shader.setMat4("model", modelMatrix);

    // Bind texture and set the shader uniform
    if (m_texture) {
        m_texture->bind();
        glActiveTexture(GL_TEXTURE0);  // Activate texture unit 0
        shader.setInt("texture1", 0);  // Set the texture sampler uniform to texture unit 0
    }

    // Render the model if it exists
    if (m_model) {
        m_model->Draw();
    }

    // Unbind the texture after rendering
    if (m_texture) {
        m_texture->unbind();
    }
}

void GameObject::Update() {
    float deltaTime = 0.016f; // Assuming 60 FPS, you can calculate this dynamically
    float rotationSpeed = 2.0f; // Degrees per second

    // Increment rotation smoothly over time
    m_rotation.y += rotationSpeed * deltaTime;
}

void GameObject::Move(const glm::vec3& direction) {
    m_position += direction;  // Move the GameObject by the direction vector
}

void GameObject::Rotate(float angle, const glm::vec3& axis) {
    m_rotation += axis * angle;  // Accumulate the rotation
}

void GameObject::SetScale(const glm::vec3& newScale) {
    m_scale = newScale;  // Set the scale of the GameObject
}

// Accessor methods
glm::vec3 GameObject::getPosition() const {
    return m_position;
}

glm::vec3 GameObject::getRotation() const {
    return m_rotation;
}

glm::vec3 GameObject::getScale() const {
    return m_scale;
}
