#pragma once
#include "Transform.h"
#include "Shader.h"
#include <vector>
#include <memory>

class Component;

class GameObject {
public:
    Transform transform;

    void AddComponent(std::unique_ptr<Component> component);
    void Update();
    void Render(Shader& shader);

    template<typename T>
    T* GetComponent();

private:
    std::vector<std::unique_ptr<Component>> components;
};