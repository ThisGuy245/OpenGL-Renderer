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
    void disableDepthTesting() const; // New method to disable depth testing
    void enableFaceCulling() const;   // New method to enable face culling
    void disableFaceCulling() const;  // New method to disable face culling
    void bind(const Mesh& mesh) const; // New method to bind a mesh
    void unbind() const;              // New method to unbind a mesh
    void draw(const class Mesh& mesh) const;
    void setWireframeMode(bool enabled) const; // New method for wireframe mode
    void enableBlending() const;      // New method to enable blending
    void disableBlending() const;     // New method to disable blending
};

#endif // RENDERER_H