#pragma once
#include "Component.h"
#include "Camera.h"
#include "GameObject.h"

class CameraComponent : public Component {
public:
    Camera camera;
    /*
    glm::mat4 GetViewMatrix() const {
        return glm::lookAt(
            gameObject->transform.position,
            gameObject->transform.position + camera.GetForward(),
            camera.GetUp()
        );
    }

    void Update() override {
        // Handle camera movement here if needed
    }*/
};