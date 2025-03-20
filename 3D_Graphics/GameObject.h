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
    Model,
    Primitive,   
    Camera,      
    Empty        
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
    GameObjectType m_type; 

    std::unique_ptr<Model> m_model; 
    std::shared_ptr<Texture> m_texture;  

    glm::vec3 m_position; 
    glm::vec3 m_rotation; 
    glm::vec3 m_scale;     
};

#endif // GAME_OBJECT_H
