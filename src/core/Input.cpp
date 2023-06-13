#include <core/Input.hpp>

#include <iostream>

namespace texplr {

Input::Input(std::shared_ptr<GameWindow> window)
    : m_window(window)
{
    m_window->getEventBus()->subscribe(this, &Input::OnKeyDown);
    m_window->getEventBus()->subscribe(this, &Input::OnKeyUp);
    m_window->getEventBus()->subscribe(this, &Input::OnMouseDown);
    m_window->getEventBus()->subscribe(this, &Input::OnMouseUp);
    m_window->getEventBus()->subscribe(this, &Input::OnMouseMove);
    m_window->getEventBus()->subscribe(this, &Input::OnScroll);
}

Input::~Input() { }

void Input::resetOffset()
{
    m_mousePositionOffset = glm::vec2(0.0f);
    m_scrollOffset = glm::vec2(0.0f);
}

bool Input::isKeyDown(KeyCodes key)
{
    return m_keyStates[key];
}

bool Input::isMouseDown(MouseButtons button)
{
    return m_buttonStates[button];
}

bool Input::isMouseLocked()
{
    return m_window->isMouseLocked();
}

const glm::vec2& Input::getMousePosition()
{
    return m_mousePosition;
}

const glm::vec2& Input::getMousePositionOffset()
{
    return m_mousePositionOffset;
}

const glm::vec2& Input::getScrollOffset()
{
    return m_scrollOffset;
}

void Input::OnKeyDown(KeyDownEvent* event)
{
    m_keyStates[event->key] = true;
}

void Input::OnKeyUp(KeyUpEvent* event)
{
    m_keyStates[event->key] = false;
}

void Input::OnMouseDown(MouseButtonDownEvent* event)
{
    m_buttonStates[event->button] = true;
}

void Input::OnMouseUp(MouseButtonUpEvent* event)
{
    m_buttonStates[event->button] = false;
}

void Input::OnMouseMove(MouseMoveEvent* event)
{
    m_mousePositionOffset = event->mousePos - m_mousePosition;
    m_mousePosition = event->mousePos;
}

void Input::OnScroll(MouseScrollEvent* event)
{
    m_scrollOffset = event->scrollOffset;
}

} // namespace texplr
