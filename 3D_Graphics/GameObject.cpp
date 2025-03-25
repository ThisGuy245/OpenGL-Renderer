#include "GameObject.h"
#include "Component.h"
#include "ModelComponent.h" // You'll need to create this
#include "Shader.h"

GameObject::GameObject(const std::string& name)
    : m_name(name),
    m_position(0.0f),
    m_rotation(0.0f),
    m_scale(1.0f),
    m_parent(nullptr) {}

GameObject::~GameObject() {
    // Remove from parent's children list if exists
    if (m_parent) {
        m_parent->RemoveChild(this);
    }

    // Clear children
    for (auto child : m_children) {
        child->m_parent = nullptr;
    }
}

void GameObject::Update(float deltaTime) {
    // Update all components
    for (auto& component : m_components) {
        component->Update(deltaTime);
    }

    // Update children
    for (auto child : m_children) {
        child->Update(deltaTime);
    }
}

void GameObject::Render(Shader& shader) {
    shader.setMat4("model", GetTransformMatrix());

    // Render all components
    for (auto& component : m_components) {
        component->Render(shader);
    }

    // Render children
    for (auto child : m_children) {
        child->Render(shader);
    }
}

Component* GameObject::AddComponentInternal(std::unique_ptr<Component> component) {
    m_components.push_back(std::move(component));
    return m_components.back().get();
}

// Transform operations
void GameObject::Translate(const glm::vec3& translation) {
    m_position += translation;
}

void GameObject::Rotate(float angle, const glm::vec3& axis) {
    m_rotation += axis * angle;
}

void GameObject::SetScale(const glm::vec3& scale) {
    m_scale = scale;
}

// Hierarchy management
void GameObject::SetParent(GameObject* parent) {
    if (m_parent) {
        m_parent->RemoveChild(this);
    }

    m_parent = parent;
    if (parent) {
        parent->AddChild(this);
    }
}

void GameObject::AddChild(GameObject* child) {
    if (child && std::find(m_children.begin(), m_children.end(), child) == m_children.end()) {
        m_children.push_back(child);
        child->m_parent = this;
    }
}

void GameObject::RemoveChild(GameObject* child) {
    auto it = std::find(m_children.begin(), m_children.end(), child);
    if (it != m_children.end()) {
        (*it)->m_parent = nullptr;
        m_children.erase(it);
    }
}

// Accessors
const glm::vec3& GameObject::GetPosition() const { return m_position; }
const glm::vec3& GameObject::GetRotation() const { return m_rotation; }
const glm::vec3& GameObject::GetScale() const { return m_scale; }

glm::mat4 GameObject::GetTransformMatrix() const {
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, m_position);
    transform = glm::rotate(transform, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
    transform = glm::rotate(transform, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
    transform = glm::scale(transform, m_scale);

    // Apply parent's transform if exists
    if (m_parent) {
        transform = m_parent->GetTransformMatrix() * transform;
    }

    return transform;
}

const std::string& GameObject::GetName() const { return m_name; }