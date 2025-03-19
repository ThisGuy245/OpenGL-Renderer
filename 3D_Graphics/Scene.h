#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "CameraComponent.h"

class Scene {
public:
    void AddGameObject(std::unique_ptr<GameObject> obj);
    void Update();
    void Render(Shader& shader);
    CameraComponent* GetMainCamera() const { return mainCamera; }
    void SetMainCamera(CameraComponent* camera) { mainCamera = camera; }

private:
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    CameraComponent* mainCamera = nullptr;
};