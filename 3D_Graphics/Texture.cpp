#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION  // Define before including
#include <stb_image.h>
#include <stdexcept>
#include <iostream>

Texture::Texture(const std::string& path)
    : m_id(0), m_width(0), m_height(0), m_channels(0), m_dirty(false) {

    unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 4);
    if (!data) {
        throw std::runtime_error("Failed to load texture: " + path);
    }

    // Copy pixel data
    m_data.assign(data, data + (m_width * m_height * 4));
    stbi_image_free(data);
    m_dirty = true;
}

Texture::~Texture() {
    if (m_id) {
        glDeleteTextures(1, &m_id);
    }
}

void Texture::bind() const {  //  Added bind()
    if (!m_id) {
        glGenTextures(1, &m_id);
        if (!m_id) {
            throw std::runtime_error("Failed to generate texture ID");
        }
    }

    if (m_dirty) {
        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data.data());
        glGenerateMipmap(GL_TEXTURE_2D);

        // Texture Wrapping & Filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        m_dirty = false;
    }

    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getID() const {
    return m_id;
}
