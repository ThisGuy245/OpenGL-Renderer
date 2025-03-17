// GameObject.h
#pragma once
#include "Mesh.h"
#include "RigidBody.h"
#include "Shader.h"

class GameObject {
public:
    Mesh mesh;
    RigidBody rigidBody;
    glm::vec3 position;
    glm::vec3 rotation;

    GameObject(Mesh mesh, RigidBody rigidBody);
    void Update(float deltaTime);
    void Render(Shader& shader);
};