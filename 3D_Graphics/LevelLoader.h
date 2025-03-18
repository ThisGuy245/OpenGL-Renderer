#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include "Scene.h"
#include "Mesh.h"
#include "Texture.h"

class LevelLoader {
public:
    static void loadDefaultLevel(Scene& scene, const Texture& defaultTexture);
};

#endif // LEVELLOADER_H