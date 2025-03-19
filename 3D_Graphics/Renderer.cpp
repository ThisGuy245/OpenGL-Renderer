#include "Renderer.h"
#include "Mesh.h"

Renderer::Renderer() {
    // Enable depth testing by default
    glEnable(GL_DEPTH_TEST);

    // Enable face culling by default
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW); // Counterclockwise faces are front-facing
}

Renderer::~Renderer() {
    // Cleanup if needed
}

void Renderer::clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setClearColor(float r, float g, float b, float a) const {
    glClearColor(r, g, b, a);
}

void Renderer::enableDepthTesting() const {
    glEnable(GL_DEPTH_TEST);
}

void Renderer::disableDepthTesting() const {
    glDisable(GL_DEPTH_TEST);
}

void Renderer::enableFaceCulling() const {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void Renderer::disableFaceCulling() const {
    glDisable(GL_CULL_FACE);
}

void Renderer::bind(const Mesh& mesh) const {
    mesh.bind(); // Assuming Mesh has a bind() method
}

void Renderer::unbind() const {
    glBindVertexArray(0);
}

void Renderer::draw(const Mesh& mesh) const {
    bind(mesh); // Bind the mesh before drawing
    mesh.draw();
    unbind();   // Unbind after drawing
}

void Renderer::setWireframeMode(bool enabled) const {
    if (enabled) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void Renderer::enableBlending() const {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::disableBlending() const {
    glDisable(GL_BLEND);
}