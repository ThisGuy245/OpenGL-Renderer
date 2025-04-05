// ModelComponent.cpp
#include "ModelComponent.h"
#include "Shader.h"

// Constructor for model files
ModelComponent::ModelComponent(Entity owner, const std::string& modelPath, const std::string& texturePath)
    : Component(),  // Explicitly call the base class constructor if needed
    m_owner(owner) {  // Initialize member variables
    // Load model from the path
    m_model = std::make_unique<Model>(modelPath);

    // Optionally, load texture
    if (!texturePath.empty()) {
        m_texture = std::make_shared<Texture>(texturePath); // Assuming Texture class has this constructor
    }
}

void ModelComponent::SetTexture(std::shared_ptr<Texture> texture) {
    m_texture = texture;
}

void ModelComponent::Render(Shader& shader) {
    // If the model has a texture, bind it
    if (m_texture) {
        m_texture->bind();                  // Bind texture
        glActiveTexture(GL_TEXTURE0);        // Set active texture unit
        shader.setInt("texture1", 0);        // Set the texture uniform to texture unit 0
    }

    // If the model is valid, draw it
    if (m_model) {
        m_model->Draw();  // Assuming your Model class has a Draw() method
    }

    // Unbind the texture if it was bound
    if (m_texture) {
        m_texture->unbind();                // Unbind texture
    }
}
