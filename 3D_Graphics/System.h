#pragma once
class ECSWorld;

class System {
public:
    System(ECSWorld* world) : world(world) {}
    virtual void update(float deltaTime) = 0;
    virtual ~System() = default;

protected:
    ECSWorld* world;
};