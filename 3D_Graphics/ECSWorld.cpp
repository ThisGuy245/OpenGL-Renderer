#include "ECSWorld.h"
#include "System.h"

Entity ECSWorld::createEntity() {
    static Entity nextEntity = 0;
    if (nextEntity >= MAX_ENTITIES) throw std::runtime_error("Max entities reached");
    entities.push_back(nextEntity);
    return nextEntity++;
}

void ECSWorld::update(float deltaTime) {
    for (auto& system : systems) {
        system->update(deltaTime);
    }
}

void ECSWorld::addSystem(std::unique_ptr<System> system) {
    systems.push_back(std::move(system));
}