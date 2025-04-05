#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "InputManager.h"

class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = -90.0f, float pitch = 0.0f);

    // Copy constructor (needed for ECS component storage)
    Camera(const Camera& other);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspectRatio) const;

    void handleMovement(const InputManager& inputManager);
    void handleMouseMovement(const InputManager& inputManager);
    void updatePosition(glm::vec3 newPosition);
    void updateOrientation(float yawOffset, float pitchOffset);

    // New getter functions
    glm::vec3 getPosition() const { return position; }
    glm::vec3 getFront() const { return front; }
    glm::vec3 getRight() const { return right; }

private:
    glm::vec3 position;
    glm::vec3 front; // C'est la direction "tout droit" pour le caméra
    glm::vec3 up; // C'est la direction "du haut" pour le caméra
    glm::vec3 right; // C'est la direction "à côté" pour le caméra
    glm::vec3 worldUp; // Garde la direction "Vers le haut" dans l'univers du Jeu

    float yaw;
    float pitch;

    void updateVectors();
};

#endif // CAMERA_H
