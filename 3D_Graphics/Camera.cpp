#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : position(position), worldUp(up), yaw(yaw), pitch(pitch) {
    updateVectors(); 
}

glm::mat4 Camera::getViewMatrix() const {  
// Matrice de Vue - ça utilise la position puis on rajoute le front pour voir ou ça regarde
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
// Matrice de projection - perspective, 45 c'est notres degrés, 0.1-100 c'est les plans de clip
    return glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
}

void Camera::handleMovement(const InputManager& inputManager) {
// Facile - les + front*0.1 c'est pour tout droit ou en arriére, la droite c'est les cotés
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
// GetMouseDelta récupere le déplacement de la souris depuis la dérniere frame
    if (inputManager.IsMouseButtonPressed(SDL_BUTTON_RIGHT)) {
        glm::vec2 mouseDelta = inputManager.GetMouseDelta();
        updateOrientation(mouseDelta.x * 0.1f, -mouseDelta.y * 0.1f);
        // X modifie le Yaw - Y modifie le Pitch
    }
}

void Camera::updatePosition(glm::vec3 newPosition) {
    position = newPosition;
}

void Camera::updateOrientation(float yawOffset, float pitchOffset) {
    yaw += yawOffset;
    pitch += pitchOffset;

    if (pitch > 89.0f) pitch = 89.0f; // Ici on bloque l'angle du pitch
    if (pitch < -89.0f) pitch = -89.0f;

    updateVectors(); // Recalculer la direction du caméra
}

void Camera::updateVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    // Cross calcule des vecteurs perpendiculaires
    right = glm::normalize(glm::cross(front, worldUp)); 
    up = glm::normalize(glm::cross(right, front));
}

