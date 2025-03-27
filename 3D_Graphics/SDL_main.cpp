#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

#include "Window.h"
#include "InputManager.h"
#include "Shader.h"
#include "Log.h"
#include "Model.h"
#include "Camera.h"
#include "Scene.h"  // Add this include
#include "GameObject.h"
#include "ModelComponent.h"
#include "Mesh.h"
#include "Primitives.h"

int SDL_main(int argc, char* argv[]) {
    // Set FPS
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    // Initialize systems
    Window window("DOOM Level", 1280, 720);
    InputManager::GetInstance().Initialize();
    Shader shader("./assets/shaders/basic.vert", "./assets/shaders/basic.frag");
    Camera camera(glm::vec3(0.0f, 1.0f, 5.0f));

    // Create scene
    Scene mainScene("MainScene");

    // Create player GameObject through scene
    GameObject* player = mainScene.CreateGameObject("Player");
    player->AddComponent<ModelComponent>(
        "./assets/models/curuthers/curuthers.obj",
        "./assets/models/curuthers/Whiskers_diffuse.png"
    );
    player->Translate(glm::vec3(0.0f, 0.0f, -2.0f)); // Position in front of camera

    // Optional: Create some test primitives through scene
    GameObject* floor = mainScene.CreateGameObject("Floor");
    floor->AddComponent<ModelComponent>(Primitives::CreatePlane(10.0f, 10.0f));
    floor->Translate(glm::vec3(0.0f, -1.0f, 0.0f));

    // Enable OpenGL features
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Projection matrix
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        1280.0f / 720.0f,
        0.1f,
        100.0f
    );

    Log::info("Application Started");

    // Main loop
    bool quit = false;
    Uint32 lastTime = SDL_GetTicks();
    while (!quit) {
        // Calculate delta time
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        // Event handling
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            InputManager::GetInstance().HandleEvent(event);
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Input and camera
        InputManager::GetInstance().Update();
        camera.handleMovement(InputManager::GetInstance());
        camera.handleMouseMovement(InputManager::GetInstance());

        // Clear screen
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set shader uniforms
        shader.use();
        shader.setMat4("view", camera.getViewMatrix());
        shader.setMat4("projection", projection);

        // Update and render entire scene
        mainScene.Update(deltaTime);
        mainScene.Render(shader);

        // Reset OpenGL state
        glBindVertexArray(0);
        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        // Swap buffers
        window.swapBuffers();
        window.pollEvents(quit);

        // Frame rate control
        Uint32 frameTime = SDL_GetTicks() - currentTime;
        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    return 0;
}