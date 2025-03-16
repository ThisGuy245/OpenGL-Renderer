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
    glm::vec2 GetMouseDelta() const;

private:
    InputManager() = default;

    // Store the current and previous mouse position
    std::unordered_map<SDL_Scancode, bool> m_keyStates;
    std::unordered_map<Uint8, bool> m_mouseButtonStates;
    glm::vec2 m_mousePosition;
    glm::vec2 m_prevMousePosition;  // Track previous mouse position
    glm::vec2 m_mouseDelta;         // Store mouse delta
};

#endif // INPUTMANAGER_H
