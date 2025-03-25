#include "ModelComponent.h"
#include "Shader.h"

ModelComponent::ModelComponent(GameObject* owner,
    const std::string& modelPath,
    const std::string& texturePath)
    : Component(owner) {
    m_model = std::make_unique<Model>(modelPath);
    if (!texturePath.empty()) {
        m_texture = std::make_shared<Texture>(texturePath, TextureType::DIFFUSE);
    }
}

void ModelComponent::Render(Shader& shader) {
    if (m_texture) {
        m_texture->bind();
        glActiveTexture(GL_TEXTURE0);
        shader.setInt("texture1", 0);
    }

    if (m_model) {
        m_model->Draw();
    }

    if (m_texture) {
        m_texture->unbind();
    }
}

void ModelComponent::SetTexture(std::shared_ptr<Texture> texture) {
    m_texture = texture;
}