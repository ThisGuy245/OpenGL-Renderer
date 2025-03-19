#include "Window.h"
#include <stdexcept>

Window::Window(const std::string& title, int width, int height)
    : width(width), height(height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Failed to initialize SDL");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


    window = SDL_CreateWindow(title.c_str(),
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!window) {
        throw std::runtime_error("Failed to create SDL window");
    }

    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        throw std::runtime_error("Failed to create OpenGL context");
    }

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to initialize GLEW");
    }



}

Window::~Window() {
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::swapBuffers() {
    SDL_GL_SwapWindow(window);
}

void Window::pollEvents(bool& quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = true;
        }
        // Handle window resizing events
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
            width = event.window.data1;
            height = event.window.data2;
            glViewport(0, 0, width, height);
        }
    }
}

int Window::getWidth() const {
    return width;
}

int Window::getHeight() const {
    return height;
}