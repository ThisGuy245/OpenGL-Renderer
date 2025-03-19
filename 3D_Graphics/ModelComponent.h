#pragma once
#include "Component.h"
#include "Model.h"
#include "Shader.h"
#include "GameObject.h"

class ModelComponent : public Component {
public:
    Model model;

    void Render(Shader& shader) override {
        shader.setMat4("model", gameObject->transform.GetModelMatrix());
        model.Draw();
    }
};