// GameObject.h
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glm/glm.hpp>
#include <string>
#include "Renderer.h"
#include "Transform.h"

class Mesh;
class Texture;
class Shader;

// GameObject.h
class GameObject {
public:
    GameObject(Mesh* mesh, Shader* shader, Texture* texture);
    void Update(float deltaTime);
    void Draw(Renderer& renderer);

    Transform transform;
private:
    Mesh* mesh;
    Shader* shader;
    Texture* texture;
};


#endif