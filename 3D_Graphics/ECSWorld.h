#pragma once

#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include "Transform.h"
#include "System.h"

using Entity = size_t;
const Entity MAX_ENTITIES = 10000;
const Entity INVALID_ENTITY = static_cast<Entity>(-1);

class System;

class ECSWorld {
public:
    // Core ECS functions
    Entity createEntity();
    void destroyEntity(Entity entity);
    void update(float deltaTime);
    void addSystem(std::unique_ptr<System> system);

    // Component management
    template<typename T> void registerComponent();
    template<typename T> bool isComponentRegistered() const;

    // Unified component addition (supports std::unique_ptr)
    template<typename T, typename... Args>
    void addComponent(Entity entity, Args&&... args);

    // Component access (supports std::unique_ptr)
    template<typename T> T& getComponent(Entity entity);
    template<typename T> const T& getComponent(Entity entity) const;
    template<typename T> bool hasComponent(Entity entity) const;

    // Entity queries
    template<typename... Components> std::vector<Entity> getEntities() const;
    template<typename... Components> bool hasAllComponents(Entity entity) const;

private:
    std::vector<Entity> entities;
    std::vector<Entity> freeList;
    std::vector<std::unique_ptr<System>> systems;
    std::unordered_map<std::type_index, std::shared_ptr<void>> componentStores;

    template<typename T> std::vector<std::unique_ptr<T>>& getComponentStore();
    template<typename T> const std::vector<std::unique_ptr<T>>& getComponentStore() const;

    void validateEntity(Entity entity) const;
};

// ==============================
// Template Implementations
// ==============================

template<typename T>
void ECSWorld::registerComponent() {
    if (isComponentRegistered<T>()) {
        throw std::runtime_error("Component already registered");
    }
    componentStores[typeid(T)] = std::make_shared<std::vector<std::unique_ptr<T>>>();
}

template<typename T>
bool ECSWorld::isComponentRegistered() const {
    return componentStores.find(typeid(T)) != componentStores.end();
}

template<typename T, typename... Args>
void ECSWorld::addComponent(Entity entity, Args&&... args) {
    validateEntity(entity);
    auto& store = getComponentStore<T>();
    if (entity >= store.size()) {
        store.resize(entity + 1);
    }
    store[entity] = std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
T& ECSWorld::getComponent(Entity entity) {
    validateEntity(entity);
    auto& store = getComponentStore<T>();
    return *store[entity];
}

template<typename T>
const T& ECSWorld::getComponent(Entity entity) const {
    validateEntity(entity);
    const auto& store = getComponentStore<T>();
    return *store[entity];
}

template<typename T>
bool ECSWorld::hasComponent(Entity entity) const {
    if (!isComponentRegistered<T>()) return false;
    const auto& store = getComponentStore<T>();
    return entity < store.size() && std::find(freeList.begin(), freeList.end(), entity) == freeList.end();
}

template<typename... Components>
std::vector<Entity> ECSWorld::getEntities() const {
    std::vector<Entity> matches;
    size_t minSize = (std::min)({ getComponentStore<Components>().size()... });

    for (Entity e = 0; e < minSize; ++e) {
        if (hasAllComponents<Components...>(e)) {
            matches.push_back(e);
        }
    }
    return matches;
}

template<typename... Components>
bool ECSWorld::hasAllComponents(Entity entity) const {
    return (hasComponent<Components>(entity) && ...);
}

template<typename T>
std::vector<std::unique_ptr<T>>& ECSWorld::getComponentStore() {
    auto it = componentStores.find(typeid(T));
    if (it == componentStores.end()) {
        throw std::runtime_error("Component not registered");
    }
    return *std::static_pointer_cast<std::vector<std::unique_ptr<T>>>(it->second);
}

template<typename T>
const std::vector<std::unique_ptr<T>>& ECSWorld::getComponentStore() const {
    auto it = componentStores.find(typeid(T));
    if (it == componentStores.end()) {
        throw std::runtime_error("Component not registered");
    }
    return *std::static_pointer_cast<const std::vector<std::unique_ptr<T>>>(it->second);
}
