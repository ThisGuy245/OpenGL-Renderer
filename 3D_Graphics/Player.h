#ifndef PLAYER_H
#define PLAYER_H

#include "Model.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <memory>

class Player {
public:
    Player(const std::string& modelPath);

    void Move(const glm::vec3& direction);
    void Rotate(float angle, const glm::vec3& axis);
    void SetScale(const glm::vec3& newScale);
    void Render(Shader& shader);

    glm::vec3 getPosition() const { return m_position; }
    glm::vec3 getRotation() const { return m_rotation; }
    glm::vec3 getScale() const { return m_scale; }

private:
    std::unique_ptr<Model> m_model;
    glm::vec3 m_position;
    glm::vec3 m_rotation; // X, Y, Z rotation in degrees
    glm::vec3 m_scale;
};

#endif
