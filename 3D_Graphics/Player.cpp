// Player.cpp
#include "Player.h"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

Player::Player()
    : position(0.0f), size(1.0f), rotationAngle(0.0f) {}

void Player::update() {
    move(0.01f);  // MOVING (currently backnforth)
    scale(1.02f); // SCALE
    rotate(2.0f); // ROTATE
}

void Player::move(float deltaTime) {
    position.x += deltaTime;
    if (position.x > 5.0f) position.x = -5.0f; // Simple back and forth movement
}

void Player::scale(float factor) {
    size = factor;
}

void Player::rotate(float angle) {
    rotationAngle += angle;
    if (rotationAngle >= 360.0f) rotationAngle -= 360.0f;
}

glm::mat4 Player::getTransform() const {
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, position);
    transform = glm::scale(transform, glm::vec3(size, size, size));
    transform = glm::rotate(transform, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    return transform;
}

glm::vec3 Player::getPosition() const {
    return position;
}
