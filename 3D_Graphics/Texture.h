#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>
#include <iostream>

class Texture {
public:
    Texture(const std::string& path);
    Texture(Texture&& other) noexcept; // Move constructor
    Texture& operator=(Texture&& other) noexcept; // Move assignment operator
    ~Texture();

    void bind() const;
    void unbind() const;
    GLuint getID() const;

private:
    GLuint m_id;
    int m_width;
    int m_height;
    int m_channels;
};

#endif // TEXTURE_H