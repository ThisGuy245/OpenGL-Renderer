#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>
#include "Model.h"
#include "Mesh.h"
#include "Shader.h"

class GameObject {
public:
    // Constructor for a Mesh-based GameObject
    GameObject(Mesh* mesh, const glm::vec3& position = glm::vec3(0.0f));

    // Constructor for a Model-based GameObject
    GameObject(Model* model, const glm::vec3& position = glm::vec3(0.0f));

    void setPosition(const glm::vec3& position);
    void setRotation(const glm::vec3& rotation);
    void setScale(const glm::vec3& scale);

    glm::vec3 getPosition() const;
    glm::vec3 getRotation() const;
    glm::vec3 getScale() const;

    void update(float deltaTime);
    void render(const Shader& shader) const;

private:
    Mesh* mesh = nullptr;
    Model* model = nullptr;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

#endif // GAMEOBJECT_H
