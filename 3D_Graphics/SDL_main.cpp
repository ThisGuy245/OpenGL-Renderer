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
#include "Mesh.h"
#include "Primitives.h"
#include "Camera.h"
#include "Scene.h"
#include "LevelLoader.h"
#include "Texture.h"

int SDL_main(int argc, char* argv[]) {
    // Set FPS
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    float deltaTime = 0.0f;

    Log::info("Application Commencé");
    // Load the default texture
    //Texture defaultTexture;

    // Initialise Window
    Window window("DOOM Level", 1280, 720);

    // Create a scene
    Scene scene;

    // Initialise LevelLoader
    //LevelLoader::loadDefaultLevel(scene, defaultTexture);

    // Initialise Input Manager
    InputManager::GetInstance().Initialize();

    // Load Shaders
    Shader shader("assets/shaders/basic.vert", "assets/shaders/basic.frag");

    // Create a Cube
    /*
    Mesh* cubeMesh = new Mesh(Primitives::CreateCube(1.0f, defaultTexture));
    GameObject cube(cubeMesh);
    cube.setPosition(glm::vec3(2.0f, 0.5f, 0.0f)); // Position the cube
    scene.addObject(cube);*/

    // Initialise Player Model
    Player playerModel("assets/models/curuthers/curuthers.obj",
        "assets/models/curuthers/Whiskers_diffuse.png");
    playerModel.setPosition(glm::vec3(-2.0f, 0.0f, 0.0f)); // Position the player
    scene.addObject(playerModel);

    // Initialise Camera 
    Camera camera(glm::vec3(0.0f, 1.0f, 5.0f));

    // OpenGL Settings
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Main loop
    bool quit = false;
    while (!quit) {
        frameStart = SDL_GetTicks();

        // Poll events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            InputManager::GetInstance().HandleEvent(event);
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Update input states (keyboard, mouse)
        InputManager::GetInstance().Update();

        // Handle camera movement and rotation based on input
        camera.handleMovement(InputManager::GetInstance());
        camera.handleMouseMovement(InputManager::GetInstance());

        // Update scene
        scene.update(deltaTime);

        // Create View & Projection Matrices
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(60.0f),
            (float)window.getWidth() / window.getHeight(),
            0.1f, 100.0f);

        // Clear the screen
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render scene
        scene.render(shader, view, projection);

        // Swap buffers
        window.swapBuffers();

        // Frame time calculation
        deltaTime = (SDL_GetTicks() - frameStart) / 1000.0f;
        if (deltaTime < frameDelay / 1000.0f) {
            SDL_Delay(frameDelay - deltaTime * 1000.0f);
        }
    }

    return 0;
}
