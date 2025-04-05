#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>
#include "Shader.h"

class GameObject;

class Component {
public:
    // Lifecycle methods
    virtual ~Component() = default;

    // Main functionality
    virtual void Start() {}      // Called when component is first added
    virtual void Update(float deltaTime) {} // Called every frame
    virtual void Render(Shader& shader) {}  // Called for rendering
    virtual std::string GetType() const = 0;  // Pure virtual function

    // Getters
    GameObject* GetGameObject() const { return m_gameObject; }
    bool IsEnabled() const { return m_enabled; }

    // Setters
    void SetEnabled(bool enabled) { m_enabled = enabled; }

protected:
    explicit Component(GameObject* gameObject)
        : m_gameObject(gameObject), m_enabled(true) {}

    // Disallow copying and assignment
    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;

private:
    GameObject* m_gameObject; // Non-owning reference
    bool m_enabled;
};

// Macro to simplify component creation
#define DECLARE_COMPONENT(type) \
    public: \
        static std::string GetStaticType() { return #type; } \
        std::string GetType() const override { return GetStaticType(); } \
    private:

#endif // COMPONENT_H