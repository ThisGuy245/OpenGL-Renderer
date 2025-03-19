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
#include "Camera.h"
#include "GameObject.h"

int SDL_main(int argc, char* argv[]) {

    // Set FPS
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    

    // Initialise Window - Initialise Fenetre
    Window window("DOOM Level", 1280, 720);

    // Initialise Input Manager - Entrée de Donées
    InputManager::GetInstance().Initialize();

    // Load Shaders - Charger Ombreurs
    Shader shader("./assets/shaders/basic.vert", "./assets/shaders/basic.frag");

    // Initialise Player & Texture - Jouer et Textures
    
    Player catModel("./assets/models/curuthers/curuthers.obj",
        "./assets/models/curuthers/Whiskers_diffuse.png");

    // TESTING adding a GameObject
    //GameObject catmodel;

    // Initialise Camera 
    Camera camera(glm::vec3(0.0f, 1.0f, 5.0f));
    
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Define camera matrices - Les vue ports et projections
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
        // Poll events - Evenements de managiere d'entrées
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            InputManager::GetInstance().HandleEvent(event);
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Frame Ticks
        Uint32 frameStart = SDL_GetTicks();

        // Update input states (keyboard, mouse)
        InputManager::GetInstance().Update();

        // Clear the screen (Couleur d'arriere plan)
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set shader uniforms - ombreurs
        shader.use();
        shader.setMat4("view", camera.getViewMatrix());
        shader.setMat4("projection", projection);

        // Handle camera movement and rotation based on input
        camera.handleMovement(InputManager::GetInstance());
        camera.handleMouseMovement(InputManager::GetInstance());

        // Render the player
        catModel.Update();
        catModel.Render(shader);

        // Reset the state
        glBindVertexArray(0);
        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        // Swap buffers
        window.pollEvents(quit);
        window.swapBuffers();

        // FPS Set
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    return 0;
}
