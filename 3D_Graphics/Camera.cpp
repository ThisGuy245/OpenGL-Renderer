#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : position(position), worldUp(up), yaw(yaw), pitch(pitch) {
    updateVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
    return glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
}

void Camera::handleMovement(const InputManager& inputManager) {
    if (inputManager.IsKeyPressed(SDL_SCANCODE_W)) {
        updatePosition(getPosition() + getFront() * 0.1f);
    }
    if (inputManager.IsKeyPressed(SDL_SCANCODE_A)) {
        updatePosition(getPosition() - getRight() * 0.1f);
    }
    if (inputManager.IsKeyPressed(SDL_SCANCODE_S)) {
        updatePosition(getPosition() - getFront() * 0.1f);
    }
    if (inputManager.IsKeyPressed(SDL_SCANCODE_D)) {
        updatePosition(getPosition() + getRight() * 0.1f);
    }
}

void Camera::handleMouseMovement(const InputManager& inputManager) {
    if (inputManager.IsMouseButtonPressed(SDL_BUTTON_RIGHT)) {
        glm::vec2 mouseDelta = inputManager.GetMouseDelta();
        updateOrientation(mouseDelta.x * 0.1f, -mouseDelta.y * 0.1f);
    }
}

void Camera::updatePosition(glm::vec3 newPosition) {
    position = newPosition;
}

void Camera::updateOrientation(float yawOffset, float pitchOffset) {
    yaw += yawOffset;
    pitch += pitchOffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    updateVectors();
}

void Camera::updateVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}