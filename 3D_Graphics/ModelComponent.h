#ifndef MODEL_COMPONENT_H
#define MODEL_COMPONENT_H

#include "Component.h"
#include "Model.h"
#include "Texture.h"

class ModelComponent : public Component {
public:
    ModelComponent(GameObject* owner, const std::string& modelPath,
        const std::string& texturePath = "");

    void Render(Shader& shader) override;

    // Model-specific functionality
    void SetTexture(std::shared_ptr<Texture> texture);
    const Model* GetModel() const { return m_model.get(); }

    DECLARE_COMPONENT(ModelComponent)

private:
    std::unique_ptr<Model> m_model;
    std::shared_ptr<Texture> m_texture;
};

#endif // MODEL_COMPONENT_H