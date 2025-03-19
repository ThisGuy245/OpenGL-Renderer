// GameObject.cpp
#include "GameObject.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"

#include <glm/gtc/matrix_transform.hpp>

GameObject::GameObject(Mesh* mesh, Texture* texture, Shader* shader)
    : m_mesh(mesh), m_texture(texture), m_shader(shader),
    m_position(0.0f, 0.0f, 0.0f), m_rotation(0.0f, 0.0f, 0.0f), m_scale(1.0f, 1.0f, 1.0f) {
    // Initialize transformation matrices
    m_modelMatrix = glm::mat4(1.0f);  // Identity matrix by default
}

void GameObject::Update(float deltaTime) {
    // For now, the update function will only affect transformations (but can be expanded)
    // You can add movement, animations, etc. here

    // Example: rotating the object slowly around the Y axis (you can replace this with your own logic)
    m_rotation.y += 30.0f * deltaTime; // Rotate 30 degrees per second
}

void GameObject::Render(const glm::mat4& view, const glm::mat4& projection) {
    // Update the model matrix based on position, rotation, and scale
    m_modelMatrix = glm::mat4(1.0f);
    m_modelMatrix = glm::translate(m_modelMatrix, m_position);
    m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotation around X
    m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotation around Y
    m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotation around Z
    m_modelMatrix = glm::scale(m_modelMatrix, m_scale); // Apply scaling

    // Use the shader for rendering
    m_shader->use();

    // Pass transformation matrices to the shader
    m_shader->setMat4("model", m_modelMatrix);
    m_shader->setMat4("view", view);
    m_shader->setMat4("projection", projection);

    // Bind texture
    m_texture->bind();

    // Bind and draw the mesh
    m_mesh->bind();
    glDrawElements(GL_TRIANGLES, m_mesh->getIndexCount(), GL_UNSIGNED_INT, 0);
}

void GameObject::SetPosition(const glm::vec3& position) {
    m_position = position;
}

glm::vec3 GameObject::GetPosition() const {
    return m_position;
}

void GameObject::SetRotation(const glm::vec3& rotation) {
    m_rotation = rotation;
}

glm::vec3 GameObject::GetRotation() const {
    return m_rotation;
}

void GameObject::SetScale(const glm::vec3& scale) {
    m_scale = scale;
}

glm::vec3 GameObject::GetScale() const {
    return m_scale;
}
