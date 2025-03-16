#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

#include "Window.h"
#include "InputManager.h"
#include "Shader.h"
#include "Player.h"
#include "Log.h"
#include "Model.h"
#include "Shader.h"

int SDL_main(int argc, char* argv[]) {
    // Initialise window
    Window window("DOOM Level", 1280, 720);

    // Initialise Input Manager
    InputManager::GetInstance().Initialize();

    // Load shaders
    Shader shader("./assets/shaders/basic.vert", "./assets/shaders/basic.frag");

    // Initialize player with model and texture
    Player catModel("./assets/models/curuthers/curuthers.obj",
        "./assets/models/curuthers/Whiskers_diffuse.png");

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Define camera matrices
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 1.0f, 5.0f), // Camera position
        glm::vec3(0.0f, 0.0f, 0.0f), // Look-at point
        glm::vec3(0.0f, 1.0f, 0.0f)); // Up direction

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), // FOV
        1280.0f / 720.0f,    // Aspect ratio
        0.1f, 100.0f);       // Near & far plane

    Log::info("Application Started");

    // Main loop
    bool quit = false;
    while (!quit) {
        // Poll events using Window's pollEvents method
        window.pollEvents(quit);

        // Update input states (keyboard, mouse)
        InputManager::GetInstance().Update();

        // Clear the screen (background color)
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set shader uniforms
        shader.bind();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        // Handle player movement and rotation based on input
        if (InputManager::GetInstance().IsKeyPressed(SDL_SCANCODE_W)) {
            catModel.Move(glm::vec3(0.0f, 0.0f, -0.1f));  // Move player forward
            Log::info("Player Moves Forwards.");
        }
        if (InputManager::GetInstance().IsKeyPressed(SDL_SCANCODE_S)) {
            catModel.Move(glm::vec3(0.0f, 0.0f, 0.1f));  // Move player backward
            Log::info("Player Moves Backwards.");
        }
        if (InputManager::GetInstance().IsKeyPressed(SDL_SCANCODE_A)) {
            catModel.Move(glm::vec3(-0.1f, 0.0f, 0.0f)); // Move player left
            Log::info("Player Turns Left.");
        }
        if (InputManager::GetInstance().IsKeyPressed(SDL_SCANCODE_D)) {
            catModel.Move(glm::vec3(0.1f, 0.0f, 0.0f));  // Move player right
            Log::info("Player Turns Right.");
        }

        // Mouse movement for rotation (adjust sensitivity if needed)
        glm::vec2 mouseDelta = InputManager::GetInstance().GetMouseDelta();
        catModel.Rotate(mouseDelta.x * 0.1f, glm::vec3(0.0f, 1.0f, 0.0f));  // Rotate player around Y-axis

        // Render the player
        catModel.Render(shader);

        // Reset the state
        glBindVertexArray(0);
        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        // Swap buffers
        window.swapBuffers();
    }
    return 0;
}
