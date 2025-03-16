#include "Window.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

#include "Shader.h"
#include "Player.h"
#include "Log.h"
#include "Model.h"

int SDL_main(int argc, char* argv[]) {
    // Initialize window
    Window window("DOOM Level", 1280, 720);

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

    // Main loop
    bool quit = false;
    while (!quit) {
        window.pollEvents(quit);

        // Clear the screen (background color)
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set shader uniforms
        shader.bind();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

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
