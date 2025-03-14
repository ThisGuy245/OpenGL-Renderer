#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>

class Window {
public:
    Window(const std::string& title, int width, int height);
    ~Window();

    void swapBuffers();
    void pollEvents(bool& quit);

    int getWidth() const;
    int getHeight() const;

private:
    SDL_Window* window;
    SDL_GLContext glContext;
    int width;
    int height;
};

#endif // WINDOW_H