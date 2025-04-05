#include "ECSWorld.h"
#include "System.h"

Entity ECSWorld::createEntity() {
    if (!freeList.empty()) {
        Entity id = freeList.back();
        freeList.pop_back();
        return id;
    }

    if (entities.size() >= MAX_ENTITIES) {
        throw std::runtime_error("Max entities reached");
    }

    Entity id = entities.size();
    entities.push_back(id);
    return id;
}

void ECSWorld::destroyEntity(Entity entity) {
    validateEntity(entity);
    freeList.push_back(entity);
}

void ECSWorld::update(float deltaTime) {
    for (auto& system : systems) {
        system->update(deltaTime);
    }
}

void ECSWorld::addSystem(std::unique_ptr<System> system) {
    systems.push_back(std::move(system));
}

void ECSWorld::validateEntity(Entity entity) const {
    if (entity >= entities.size() ||
        std::find(freeList.begin(), freeList.end(), entity) != freeList.end()) {
        throw std::invalid_argument("Invalid entity ID");
    }
}
