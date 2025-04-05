#include <SDL2/SDL.h>
#include "Window.h"
#include "Log.h"
#include "ECSWorld.h"
#include "Transform.h"
#include "CameraComponent.h"
#include "RenderSystem.h"
#include "ModelComponent.h"

int main() {
    // Initialize the window and log system
    Window window("ECS Demo", 1280, 720);
    Log::info("Step 2: Rendering a model");

    // Create ECS World
    ECSWorld world;
    world.registerComponent<CameraComponent>();
    world.registerComponent<ModelComponent>();
    world.registerComponent<Transform>();

    // Create camera entity
    Entity cameraEntity = world.createEntity();
    world.addComponent<CameraComponent>(cameraEntity,
        glm::vec3(0, 0, 5),   // position
        glm::vec3(0, 1, 0),   // up
        -90.0f,               // yaw
        0.0f                  // pitch
    );
    world.getComponent<CameraComponent>(cameraEntity).isMainCamera = true;

    // Create systems
    world.addSystem(std::make_unique<RenderSystem>(&world));

    // Create the model entity
    Entity modelEntity = world.createEntity();
    Transform modelTransform = {/* Set your transform data here (position, rotation, scale) */ };
    world.addComponent<Transform>(modelEntity, modelTransform);

    // Create ModelComponent and add it to ECS
    auto modelComponent = std::make_unique<ModelComponent>(
        modelEntity,
        "./assets/models/curuthers/curuthers.obj",  // Model path
        "./assets/models/curuthers/Whiskers_diffuse.png"  // Texture path
    );
    world.addComponent<ModelComponent>(modelEntity, std::move(modelComponent));

    // Main loop
    bool quit = false;
    while (!quit) {
        window.pollEvents(quit);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update ECS world (for systems)
        world.update(1.0f / 60.0f);

        // Swap buffers for rendering
        window.swapBuffers();
    }

    return 0;
}
