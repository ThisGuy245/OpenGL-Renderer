#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <stdexcept>

Texture::Texture(const std::string& path, TextureType type, bool srgb)
    : m_id(0), m_width(0), m_height(0), m_channels(0), m_type(type) {

    // Load image - Charger l'image
    unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 0);
    if (!data) {
        throw std::runtime_error("Failed to load texture: " + path);
    }

    GLenum internalFormat, format;
    if (m_channels == 4) {
        internalFormat = srgb ? GL_SRGB_ALPHA : GL_RGBA;
        format = GL_RGBA;
    }
    else if (m_channels == 3) {
        internalFormat = srgb ? GL_SRGB : GL_RGB;
        format = GL_RGB;
    }
    else {
        throw std::runtime_error("Unsupported texture format in: " + path);
    }

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
}

Texture::~Texture() {
    if (m_id) {
        glDeleteTextures(1, &m_id);
        std::cout << "Deleted texture: " << m_id << std::endl;
    }
}

void Texture::bind(GLuint unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getID() const {
    return m_id;
}

TextureType Texture::getType() const {
    return m_type;
}

Texture::Texture(Texture&& other) noexcept
    : m_id(other.m_id), m_width(other.m_width), m_height(other.m_height),
    m_channels(other.m_channels), m_type(other.m_type) {
    other.m_id = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept {
    if (this != &other) {
        glDeleteTextures(1, &m_id);

        m_id = other.m_id;
        m_width = other.m_width;
        m_height = other.m_height;
        m_channels = other.m_channels;
        m_type = other.m_type;

        other.m_id = 0;
    }
    return *this;
}
