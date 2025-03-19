#pragma once
class GameObject;
class Shader;

class Component {
public:
    virtual void Update() {}
    virtual void Render(Shader& shader) {}
    virtual ~Component() = default;
    GameObject* gameObject = nullptr;
};