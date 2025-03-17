#ifndef PRIMITIVES_H
#define PRIMITIVES_H
#include "Mesh.h"

class Primitives {
public:
    static Mesh CreateCube(float size);
    static Mesh CreateSphere(float radius, int segments);
    static Mesh CreatePlane(float width, float height);
};

#endif