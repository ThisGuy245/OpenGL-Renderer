#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>
#include <iostream>

enum class TextureType {
    DIFFUSE,
    SPECULAR,
    NORMAL,
    HEIGHT
};

class Texture {
public:
    Texture(const std::string& path, TextureType type, bool srgb = false);
    ~Texture();

    // Disable copy semantics
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    // Enable move semantics
    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    void bind(GLuint unit = 0) const;
    void unbind() const;
    GLuint getID() const;
    TextureType getType() const;

private:
    GLuint m_id;
    int m_width, m_height, m_channels;
    TextureType m_type;
};

#endif