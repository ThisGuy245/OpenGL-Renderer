#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "Window.h"
#include "Log.h"
#include "ECSWorld.h"
#include "Transform.h"
#include "CameraComponent.h"
#include "RenderSystem.h"
#include "Mesh.h"  // Your existing Mesh class

int main() {
    Window window("ECS Demo", 1280, 720);
    Log::info("Step 2: Rendering a model");

    ECSWorld world;

    // --- SETUP CAMERA ---
    // Register component types first
    world.registerComponent<Transform>();
    world.registerComponent<Mesh>();
    world.registerComponent<CameraComponent>();

    // Create systems
    world.addSystem(std::make_unique<RenderSystem>(&world));

    // Create entities
    Entity camera = world.createEntity();
    world.addComponent<CameraComponent>(camera, {/* init camera */ });
    world.getComponent<CameraComponent>(camera).isMainCamera = true;

    Entity model = world.createEntity();
    world.addComponent<Transform>(model, {/* init transform */ });
    //world.addComponent<Mesh>(model, {/* init mesh */ });

    // Main loop
    bool quit = false;
    while (!quit) {
        window.pollEvents(quit);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        world.update(1.0f / 60.0f);
        window.swapBuffers();
    }
    return 0;
}