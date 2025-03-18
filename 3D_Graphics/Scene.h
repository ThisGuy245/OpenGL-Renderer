#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "GameObject.h"

class Scene {
public:
    void addObject(GameObject& object);
    void update(float deltaTime);
    void render(const Shader& shader, const glm::mat4& view, const glm::mat4& projection) const;

private:
    std::vector<GameObject*> objects;
};

#endif // SCENE_H