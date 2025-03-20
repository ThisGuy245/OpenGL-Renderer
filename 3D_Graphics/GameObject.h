// GameObject.h
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glm/glm.hpp>
#include <string>
#include "Renderer.h"
#include "Transform.h"

class Model;
class Texture;
class Shader;

// GameObject.h
class GameObject {
public:
    GameObject(Model* model, Shader* shader, Texture* texture);
    void Update();
    void Draw(Renderer& renderer);

    Transform transform;
private:
    Model* model;
    Shader* shader;
    Texture* texture;
};


#endif