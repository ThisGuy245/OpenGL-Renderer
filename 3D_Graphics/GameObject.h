#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include <string>
#include <glm/glm.hpp>
#include <memory>

// Enum to specify the type of object
enum class GameObjectType {
    Model,       // Model loaded from file
    Primitive,   // Primitive like Cube, Sphere, etc.
    Camera,      // Camera object
    Empty        // Empty GameObject, no model or texture
};

class GameObject {
public:
    // Constructor for GameObject
    GameObject(const std::string& modelPath, GameObjectType type, const std::string& texturePath = "");

    // Update the GameObject (rotation, position, etc.)
    void Update();

    // Render the GameObject using a shader
    void Render(Shader& shader);

    // Movement functions
    void Move(const glm::vec3& direction);
    void Rotate(float angle, const glm::vec3& axis);
    void SetScale(const glm::vec3& newScale);

    // Accessor functions for transformations
    glm::vec3 getPosition() const;
    glm::vec3 getRotation() const;
    glm::vec3 getScale() const;

private:
    GameObjectType m_type;  // Type of the GameObject (Model, Primitive, Camera, Empty)

    std::unique_ptr<Model> m_model;  // The model associated with the GameObject (null if primitive or empty)
    std::shared_ptr<Texture> m_texture;  // The texture for the model (null if no texture)

    glm::vec3 m_position;  // Position of the GameObject
    glm::vec3 m_rotation;  // Rotation of the GameObject
    glm::vec3 m_scale;     // Scale of the GameObject
};

#endif // GAME_OBJECT_H
