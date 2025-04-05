#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>
#include "Shader.h"
#include "ECSWorld.h"  // Assuming you have access to ECSWorld for Entity

class Component {
public:
    // Lifecycle methods
    Component() = default;
    virtual ~Component() = default;

    // Main functionality
    virtual void Start() {}      // Called when component is first added
    virtual void Update(float deltaTime) {} // Called every frame
    virtual void Render(Shader& shader) {}  // Called for rendering
    virtual std::string GetType() const = 0;  // Pure virtual function

    // Getter
    Entity GetEntity() const { return m_entity; }
    bool IsEnabled() const { return m_enabled; }

    // Setter
    void SetEnabled(bool enabled) { m_enabled = enabled; }

protected:
    explicit Component(Entity entity) // Now accept Entity instead of GameObject*
        : m_entity(entity), m_enabled(true) {
    }

    // Disallow copying and assignment
    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;

private:
    Entity m_entity;  // Entity that owns this component
    bool m_enabled;
};

#define DECLARE_COMPONENT(type) \
    public: \
        static std::string GetStaticType() { return #type; } \
        std::string GetType() const override { return GetStaticType(); } \
    private:

#endif // COMPONENT_H
