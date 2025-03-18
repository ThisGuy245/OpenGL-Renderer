#include "InputManager.h"
#include "Log.h"

InputManager& InputManager::GetInstance() {
    static InputManager instance;
    return instance;
}

void InputManager::Initialize() {
    SDL_StartTextInput();  // Start text input for handling text input events
    m_prevMousePosition = glm::vec2(0.0f, 0.0f); // Initialize previous mouse position
}

void InputManager::Update() {
    // Update mouse delta
    m_mouseDelta = m_mousePosition - m_prevMousePosition;

    // Update the previous mouse position for the next frame
    m_prevMousePosition = m_mousePosition;
}

void InputManager::HandleEvent(const SDL_Event& e) {
    switch (e.type) {
    case SDL_KEYDOWN:
        m_keyStates[e.key.keysym.scancode] = true;
        break;
    case SDL_KEYUP:
        m_keyStates[e.key.keysym.scancode] = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        m_mouseButtonStates[e.button.button] = true;
        break;
    case SDL_MOUSEBUTTONUP:
        m_mouseButtonStates[e.button.button] = false;
        break;
    case SDL_MOUSEMOTION:
        m_mousePosition = glm::vec2(static_cast<float>(e.motion.x), static_cast<float>(e.motion.y));
        break;
    default:
        break;
    }
}

bool InputManager::IsKeyPressed(SDL_Scancode key) const {
    auto it = m_keyStates.find(key);
    return it != m_keyStates.end() && it->second;
}

bool InputManager::IsMouseButtonPressed(Uint8 button) const {
    auto it = m_mouseButtonStates.find(button);
    return it != m_mouseButtonStates.end() && it->second;
}

glm::vec2 InputManager::GetMousePosition() const {
    return m_mousePosition;
}

glm::vec2 InputManager::GetMouseDelta() const {
    return m_mouseDelta; 
}
