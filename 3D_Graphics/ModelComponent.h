// ModelComponent.h
#ifndef MODEL_COMPONENT_H
#define MODEL_COMPONENT_H

#include "Component.h"
#include "Model.h"
#include "Texture.h"
#include "ECSWorld.h"
#include <memory>
#include <string>

class ModelComponent : public Component {
public:
    // Constructor for loading model and texture from file
    ModelComponent(Entity owner, const std::string& modelPath, const std::string& texturePath = "");

    // Delete copy constructor and copy assignment operator
    ModelComponent(const ModelComponent&) = delete;
    ModelComponent& operator=(const ModelComponent&) = delete;

    // Rendering function
    void Render(Shader& shader) override;

    // Set texture for the model
    void SetTexture(std::shared_ptr<Texture> texture);

    // Getter for model
    const Model* GetModel() const { return m_model.get(); }

    // Component declaration macro
    DECLARE_COMPONENT(ModelComponent)

private:
    Entity m_owner;                  // Entity owner
    std::unique_ptr<Model> m_model;   // The model (unique to this component)
    std::shared_ptr<Texture> m_texture; // Optional texture for the model
};

#endif // MODEL_COMPONENT_H
