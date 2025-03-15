#include "Player.h"

Player::Player(const std::string& modelPath)
    : m_position(0.0f, 0.0f, 0.0f),
    m_rotation(0.0f, 0.0f, 0.0f),
    m_scale(1.0f, 1.0f, 1.0f) {

    m_model = std::make_unique<Model>(modelPath);
}

void Player::Move(const glm::vec3& direction) {
    m_position += direction;
}

void Player::Rotate(float angle, const glm::vec3& axis) {
    m_rotation += angle * axis;
}

void Player::SetScale(const glm::vec3& newScale) {
    m_scale = newScale;
}

void Player::Render(Shader& shader) {
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, m_position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::scale(modelMatrix, m_scale);

    shader.setMat4("model", modelMatrix);  
    m_model->Draw();
}