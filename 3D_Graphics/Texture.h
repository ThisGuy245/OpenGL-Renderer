#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>
#include <vector>

class Texture {
public:
    Texture(const std::string& path);
    ~Texture();

    void bind();
    void unbind() const;
    GLuint getID() const;

private:
    std::vector<unsigned char> m_data;
    GLuint m_id;
    int m_width;
    int m_height;
    int m_channels;
    bool m_dirty;
};

#endif
