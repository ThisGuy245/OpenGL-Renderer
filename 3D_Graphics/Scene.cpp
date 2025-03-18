#include "Scene.h"

void Scene::addObject(GameObject& object) {
    objects.push_back(&object);
}

void Scene::update(float deltaTime) {
    for (auto& object : objects) {
        object->update(deltaTime);
    }
}

void Scene::render(const Shader& shader, const glm::mat4& view, const glm::mat4& projection) const {
    shader.use();

    for (const auto& object : objects) {
        object->render(shader);
    }
}