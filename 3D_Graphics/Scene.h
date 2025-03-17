// Scene.h
#pragma once
#include <vector>
#include "GameObject.h"

class Scene {
public:
    std::vector<GameObject> objects;

    void AddObject(const GameObject& object);
    void Update(float deltaTime);
    void Render(Shader& shader);
};