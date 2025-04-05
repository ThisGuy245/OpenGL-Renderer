#pragma once
#include "Camera.h"

struct CameraComponent {
    Camera camera;
    bool isMainCamera = false;

    // Default constructor (needed for ECS)
    CameraComponent() : camera() {}  // Uses Camera's default constructor

    // Simplified constructor
    CameraComponent(const glm::vec3& position, const glm::vec3& up)
        : camera(position, up, -90.0f, 0.0f) {
    }

    // Full constructor
    CameraComponent(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch)
        : camera(position, up, yaw, pitch) {
    }
};