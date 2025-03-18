#include "Player.h"

Player::Player(const std::string& modelPath, const std::string& texturePath)
    : GameObject(static_cast<Model*>(nullptr), glm::vec3(0.0f)) // Disambiguate call
{
    m_model = std::make_unique<Model>(modelPath);
    m_texture = std::make_unique<Texture>(texturePath);
}



void Player::Move(const glm::vec3& direction) {
    setPosition(getPosition() + direction); // Use GameObject's setPosition
}

void Player::Rotate(float angle, const glm::vec3& axis) {
    setRotation(getRotation() + axis * angle); // Use GameObject's setRotation
}

void Player::SetScale(const glm::vec3& newScale) {
    setScale(newScale); // Use GameObject's setScale
}

void Player::Update() {
    float deltaTime = 0.016f; // Assuming 60 FPS, calculate this dynamically
    float rotationSpeed = 2.0f; // Degrees per second

    // Increment rotation smoothly over time
    Rotate(rotationSpeed * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around the Y-axis

    // Call the base class update method
    GameObject::update(deltaTime);
}