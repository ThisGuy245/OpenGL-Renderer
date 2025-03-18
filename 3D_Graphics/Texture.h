#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>
#include <vector>

// Texture.h

class Texture {
public:
    Texture(const std::string& path); // Existing constructor
    Texture(); // New constructor for default texture
    ~Texture();

    void bind() const;
    void unbind() const;
    GLuint getID() const;

private:
    std::vector<unsigned char> m_data;
    mutable GLuint m_id;
    int m_width;
    int m_height;
    int m_channels;
    mutable bool m_dirty;
};


#endif
