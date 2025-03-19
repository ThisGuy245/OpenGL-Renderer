#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"

class Scene {
public:
    void AddGameObject(std::unique_ptr<GameObject> obj);
    void Update();
    void Render(Shader& shader);


private:
    std::vector<std::unique_ptr<GameObject>> gameObjects;

};