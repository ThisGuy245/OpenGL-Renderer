// GameObject.h
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glm/glm.hpp>
#include <string>

class Mesh;
class Texture;
class Shader;

class GameObject {
public:
    // Constructor
    GameObject(Mesh* mesh, Texture* texture, Shader* shader);

    // Update the object's state (e.g., movement, animations)
    void Update(float deltaTime);

    // Render the object
    void Render(const glm::mat4& view, const glm::mat4& projection);

    // Setters/Getters for transform
    void SetPosition(const glm::vec3& position);
    glm::vec3 GetPosition() const;

    void SetRotation(const glm::vec3& rotation);
    glm::vec3 GetRotation() const;

    void SetScale(const glm::vec3& scale);
    glm::vec3 GetScale() const;

private:
    Mesh* m_mesh;
    Texture* m_texture;
    Shader* m_shader;

    glm::vec3 m_position;    // Position of the object
    glm::vec3 m_rotation;    // Rotation (in degrees or radians)
    glm::vec3 m_scale;       // Scale factor

    // Transformation matrices
    glm::mat4 m_modelMatrix; // Model matrix (for transformation)
};

#endif
