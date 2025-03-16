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
    modelMatrix = glm::translate(modelMatrix, m_position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::scale(modelMatrix, m_scale);

    shader.setMat4("model", modelMatrix);

    m_texture->bind(); // Bind the texture before drawing
    m_model->Draw();
    m_texture->unbind();
}
