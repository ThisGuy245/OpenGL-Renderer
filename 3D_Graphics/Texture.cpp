#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <stdexcept>
#include <iostream>
#include <filesystem>
#include "Log.h"

Texture::Texture(const std::string& path)
    : m_id(0), m_width(0), m_height(0), m_channels(0), m_dirty(false) {

    Log::info("Loading texture from: " + path);

    // Load texture data
    unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 4);
    if (!data) {
        Log::error("Failed to load texture: " + path + ". Falling back to default texture.");
        createDefaultTexture();
        return;
    }

    // Generate and bind the texture
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    // Upload texture data to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Free the loaded image data
    stbi_image_free(data);
    m_dirty = false; // Texture is now uploaded to GPU

    Log::info("Texture Loaded: " + path);
    Log::info("Generated Texture ID: " + std::to_string(m_id));
}

void Texture::createDefaultTexture() {
    // Generate a texture ID
    glGenTextures(1, &m_id);
    if (m_id == 0) {
        Log::error("Failed to generate texture ID for default texture.");
        return;
    }

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, m_id);

    // Create a 1x1 white pixel
    unsigned char pixel[] = { 255, 255, 255, 255 }; // RGBA white
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    Log::info("Default texture created with ID: " + std::to_string(m_id));
}

void Texture::bind() const {
    if (m_id == 0) {
        Log::error("Error: Texture has an invalid ID!");
        return;
    }
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getID() const {
    return m_id;
}
Texture::~Texture() {
    if (m_id) {
        glDeleteTextures(1, &m_id);
    }
}