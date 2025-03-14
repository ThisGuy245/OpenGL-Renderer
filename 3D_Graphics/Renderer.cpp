#include "Renderer.h"
#include "Mesh.h" 

Renderer::Renderer() {
    glEnable(GL_DEPTH_TEST);
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

void Renderer::draw(const Mesh& mesh) const {
    mesh.draw();
}