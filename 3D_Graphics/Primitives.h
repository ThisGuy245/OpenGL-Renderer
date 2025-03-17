#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "Mesh.h"

class Primitives {
public:
    static Mesh CreateCube(float size, const Texture& defaultTexture);
    static Mesh CreateSphere(float radius, int segments, const Texture& defaultTexture);
    static Mesh CreatePlane(float width, float height, const Texture& defaultTexture);
};

#endif