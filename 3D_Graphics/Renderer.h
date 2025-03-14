#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Mesh.h"

class Mesh;

class Renderer {
public:
    Renderer();
    ~Renderer();

    void clear() const;
    void setClearColor(float r, float g, float b, float a) const;
    void enableDepthTesting() const;
    void draw(const class Mesh& mesh) const;
};

#endif // RENDERER_H