#pragma once
#include "Transform.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "Mesh.h"
#include <vector>
#include <memory>

class Component;

class GameObject {
public:
    Transform transform;
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Texture> texture;
    std::shared_ptr<Shader> shader;

    virtual void Update(float deltaTime) {}
    virtual void Render(Renderer& renderer) {
        shader->use();
        texture->bind();
        mesh->draw();
    }
};
