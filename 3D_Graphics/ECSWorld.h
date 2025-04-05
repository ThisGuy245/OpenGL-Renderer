#pragma once
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>
#include <stdexcept>

using Entity = size_t;
const Entity MAX_ENTITIES = 10000;

class System; // Forward declaration

class ECSWorld {
public:
    // Core ECS functions
    Entity createEntity();
    void update(float deltaTime);
    void addSystem(std::unique_ptr<System> system);

    // Component management
    template<typename T> void registerComponent();
    template<typename T> void addComponent(Entity entity, T component);
    template<typename T> T& getComponent(Entity entity);
    template<typename T> bool hasComponent(Entity entity);
    template<typename... Components> std::vector<Entity> getEntities();

private:
    std::vector<Entity> entities;
    std::vector<std::unique_ptr<System>> systems;
    std::unordered_map<std::type_index, std::shared_ptr<void>> componentStores;

    template<typename T> std::vector<T>& getComponentStore();
};

// Component management implementations...

template<typename T>
void ECSWorld::registerComponent() {
    componentStores[typeid(T)] = std::make_shared<std::vector<T>>();
}

template<typename T>
void ECSWorld::addComponent(Entity entity, T component) {
    auto& store = getComponentStore<T>();
    if (entity >= store.size()) store.resize(entity + 1);
    store[entity] = component;
}

template<typename T>
T& ECSWorld::getComponent(Entity entity) {
    return getComponentStore<T>()[entity];
}

template<typename T>
bool ECSWorld::hasComponent(Entity entity) {
    auto& store = getComponentStore<T>();
    return entity < store.size();
}

template<typename... Components>
std::vector<Entity> ECSWorld::getEntities() {
    std::vector<Entity> matches;
    size_t minSize = (std::min)({ getComponentStore<Components>().size()... });

    for (Entity e = 0; e < minSize; e++) {
        if ((hasComponent<Components>(e) && ...)) {
            matches.push_back(e);
        }
    }
    return matches;
}

template<typename T>
std::vector<T>& ECSWorld::getComponentStore() {
    auto it = componentStores.find(typeid(T));
    if (it == componentStores.end()) throw std::runtime_error("Component not registered");
    return *static_cast<std::vector<T>*>(it->second.get());
}
