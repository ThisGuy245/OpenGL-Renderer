// GameObject.h
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>


// GameObject.h
class GameObject {
public:
    GameObject(const std::string& modelPath, const std::string& texturePath);
    void Update();
    void Render(Shader& shader);

    void Move(const glm::vec3& direction);
    void Rotate(float angle, const glm::vec3& axis);
    void SetScale(const glm::vec3& newScale);

    Transform transform;

    glm::vec3 getPosition() const { return m_position; }
    glm::vec3 getRotation() const { return m_rotation; }
    glm::vec3 getScale() const { return m_scale; }
private:
    std::unique_ptr<Model> m_model;
    std::shared_ptr<Texture> m_texture;

    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
};


#endif