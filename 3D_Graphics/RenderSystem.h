#pragma once
#include "System.h"
#include "Transform.h"
#include "Mesh.h"
#include "CameraComponent.h"
#include "Renderer.h"

class RenderSystem : public System {
public:
    RenderSystem(ECSWorld* world) : System(world) {}

    void update(float deltaTime) override {
        auto& camera = getMainCamera();

        for (Entity entity : world->getEntities<Transform, Mesh>()) {
            auto& transform = world->getComponent<Transform>(entity);
            auto& mesh = world->getComponent<Mesh>(entity);

            Renderer renderer;
            renderer.draw(mesh);
        }
    }

private:
    Camera& getMainCamera() {
        for (Entity entity : world->getEntities<CameraComponent>()) {
            auto& camComp = world->getComponent<CameraComponent>(entity);
            if (camComp.isMainCamera) return camComp.camera;
        }
        throw std::runtime_error("No main camera found!");
    }
};

