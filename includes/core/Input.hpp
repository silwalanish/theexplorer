#pragma once

#include <map>
#include <memory>

#include <core/Events.hpp>
#include <core/GameWindow.hpp>
#include <core/KeyCodes.hpp>

namespace texplr {

class Input {
public:
    Input(std::shared_ptr<GameWindow> window);
    ~Input();

    bool isKeyDown(KeyCodes key);
    bool isMouseDown(MouseButtons button);
    bool isMouseLocked();

    const glm::vec2& getMousePosition();
    const glm::vec2& getScrollOffset();

private:
    glm::vec2 m_mousePosition = glm::vec2(0.0f);
    glm::vec2 m_mousePositionOffset = glm::vec2(0.0f);
    glm::vec2 m_scrollOffset = glm::vec2(0.0f);

    std::map<KeyCodes, bool> m_keyStates;
    std::map<MouseButtons, bool> m_buttonStates;
    std::shared_ptr<GameWindow> m_window;

    void OnKeyDown(KeyDownEvent* event);
    void OnKeyUp(KeyUpEvent* event);

    void OnMouseDown(MouseButtonDownEvent* event);
    void OnMouseUp(MouseButtonUpEvent* event);

    void OnMouseMove(MouseMoveEvent* event);
    void OnScroll(MouseScrollEvent* event);
};

} // namespace texplr
