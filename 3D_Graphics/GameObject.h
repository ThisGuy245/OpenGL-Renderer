#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>
#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Component.h"

class Model;
class Texture;
class Shader;
class Component;

class GameObject {
public:
    GameObject(const std::string& name = "GameObject");
    ~GameObject();

    // Core functionality
    void Update(float deltaTime);
    void Render(Shader& shader);

    // Component management
    template<typename T, typename... Args>
    T* AddComponent(Args&&... args);

    template<typename T>
    T* GetComponent();

    template<typename T>
    bool RemoveComponent();

    // Transform operations
    void Translate(const glm::vec3& translation);
    void Rotate(float angle, const glm::vec3& axis);
    void SetScale(const glm::vec3& scale);

    // Hierarchy management
    void SetParent(GameObject* parent);
    void AddChild(GameObject* child);
    void RemoveChild(GameObject* child);

    // Accessors
    const glm::vec3& GetPosition() const;
    const glm::vec3& GetRotation() const;
    const glm::vec3& GetScale() const;
    glm::mat4 GetTransformMatrix() const;
    const std::string& GetName() const;

private:
    std::string m_name;
    glm::vec3 m_position;
    glm::vec3 m_rotation; // Stored as Euler angles in degrees
    glm::vec3 m_scale;

    std::vector<std::unique_ptr<Component>> m_components;
    GameObject* m_parent;
    std::vector<GameObject*> m_children;

    // Helper for component operations
    Component* AddComponentInternal(std::unique_ptr<Component> component);
};

// Template implementations must be in header
template<typename T, typename... Args>
T* GameObject::AddComponent(Args&&... args) {
    static_assert(std::is_base_of<Component, T>::value,
        "T must inherit from Component");
    auto component = std::make_unique<T>(this, std::forward<Args>(args)...);
    return static_cast<T*>(AddComponentInternal(std::move(component)));
}

template<typename T>
T* GameObject::GetComponent() {
    for (auto& component : m_components) {
        if (dynamic_cast<T*>(component.get())) {
            return static_cast<T*>(component.get());
        }
    }
    return nullptr;
}

template<typename T>
bool GameObject::RemoveComponent() {
    for (auto it = m_components.begin(); it != m_components.end(); ++it) {
        if (dynamic_cast<T*>(it->get())) {
            m_components.erase(it);
            return true;
        }
    }
    return false;
}

#endif // GAME_OBJECT_H