#include "Player.h"

Player::Player(const std::string& modelPath, const std::string& texturePath)
    : m_position(0.0f, 0.0f, 0.0f),
    m_rotation(0.0f, 0.0f, 0.0f),
    m_scale(1.0f, 1.0f, 1.0f) {
    m_model = std::make_unique<Model>(modelPath);
    m_texture = std::make_unique<Texture>(texturePath);
}

void Player::Render(Shader& shader) {
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    // Apply transformations
    modelMatrix = glm::translate(modelMatrix, m_position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::scale(modelMatrix, m_scale);

    // Set model matrix in the shader
    shader.setMat4("model", modelMatrix);

    // Bind texture and set the shader uniform
    m_texture->bind();
    glActiveTexture(GL_TEXTURE0);  // Activate texture unit 0
    shader.setInt("texture1", 0);  // Set the texture sampler uniform to texture unit 0

    // Render the model
    m_model->Draw();

    // Unbind texture after rendering
    m_texture->unbind();
}

void Player::Update() {
    float deltaTime = 0.016f; // Assuming 60 FPS, you can calculate this dynamically
    float rotationSpeed = 2.0f; // Degrees per second

    // Increment rotation smoothly over time
    m_rotation.y += rotationSpeed * deltaTime;
}


void Player::Move(const glm::vec3& direction) {
    m_position += direction;  // Move the player by the direction vector
}

void Player::Rotate(float angle, const glm::vec3& axis) {
    m_rotation += axis * angle;  // Accumulate the rotation
}

void Player::SetScale(const glm::vec3& newScale) {
    m_scale = newScale;  // Set the scale of the player
}
