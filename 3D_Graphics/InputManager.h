#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL2/SDL.h>
#include <unordered_map>
#include <glm/glm.hpp>

class InputManager {
public:
    static InputManager& GetInstance();

    void Initialize();
    void Update();
    void HandleEvent(const SDL_Event& e);

    bool IsKeyPressed(SDL_Scancode key) const;
    bool IsMouseButtonPressed(Uint8 button) const;
    glm::vec2 GetMousePosition() const;

private:
    InputManager() = default;

    std::unordered_map<SDL_Scancode, bool> m_keyStates;
    std::unordered_map<Uint8, bool> m_mouseButtonStates;
    glm::vec2 m_mousePosition;
};

#endif // INPUTMANAGER_H
