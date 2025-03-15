#include "Window.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>
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

    // Initialize player
    Player catModel("./assets/models/curuthers/curuthers.obj");

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Main loop
    bool quit = false;
    while (!quit) {
        window.pollEvents(quit);

        // Clear the screen (background color)
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Set background color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set shader uniforms
        shader.bind();
        shader.setMat4("model", glm::mat4(1.0f));  // Model transformation matrix
        shader.setMat4("view", glm::mat4(1.0f));   // View matrix
        shader.setMat4("projection", glm::mat4(1.0f)); // Projection matrix

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