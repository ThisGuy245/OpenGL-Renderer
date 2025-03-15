#include "Window.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Player.h"
#include "Log.h"

int SDL_main(int argc, char* argv[]) {
    // Initialize window
    Window window("DOOM Level", 1280, 720);

    // Load shaders
    Shader shader("shaders/basic.vert", "shaders/basic.frag");

    // Initialize player
    Player player("assets/curuthers.obj");

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
        player.Render(shader);

        // Swap buffers
        window.swapBuffers();
    }
    return 0;
}