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
    Shader shader("assets/shaders/vertex_shader.glsl", "assets/shaders/fragment_shader.glsl");

    // Initialize player
    Player player;

    // Main loop
    bool quit = false;
    while (!quit) {
        window.pollEvents(quit);

        // Update player
        player.update();

        // Clear the screen (background color)
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Set background color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set shader uniforms
        shader.use();
        shader.setUniformMatrix4fv("model", glm::value_ptr(player.getTransform()));       // Player model matrix

        // Render player (You can load the model and bind it here)
        // player.render(); // Example if you have a render method for the player model.

        // Swap buffers
        window.swapBuffers();
    }
    return 0;
}