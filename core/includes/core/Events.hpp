#pragma once

#include <glm/glm.hpp>

#include <core/EntityHandle.hpp>
#include <core/Event.hpp>
#include <core/KeyCodes.hpp>

namespace texplr {

class GameWindow;

struct KeyDownEvent : public Event {
    const KeyCodes key;

    KeyDownEvent(KeyCodes key)
        : key(key)
    {
    }
};

struct KeyUpEvent : public Event {
    const KeyCodes key;

    KeyUpEvent(KeyCodes key)
        : key(key)
    {
    }
};

struct WindowCloseEvent : public Event {
    const GameWindow* window;

    WindowCloseEvent(const GameWindow* window)
        : window(window)
    {
    }
};

struct MouseMoveEvent : public Event {
    const glm::vec2 mousePos;

    MouseMoveEvent(const glm::vec2& mousePos)
        : mousePos(mousePos)
    {
    }
};

struct MouseButtonDownEvent : public Event {
    const MouseButtons button;

    MouseButtonDownEvent(MouseButtons button)
        : button(button)
    {
    }
};

struct MouseButtonUpEvent : public Event {
    const MouseButtons button;

    MouseButtonUpEvent(MouseButtons button)
        : button(button)
    {
    }
};

struct MouseScrollEvent : public Event {
    const glm::vec2 scrollOffset;

    MouseScrollEvent(const glm::vec2& scrollOffset)
        : scrollOffset(scrollOffset)
    {
    }
};

struct EntityCreatedEvent : public Event {
    const EntityHandle entity;

    EntityCreatedEvent(EntityHandle entity)
        : entity(entity)
    {
    }
};

struct EntityDestroyedEvent : public Event {
    const EntityHandle entity;

    EntityDestroyedEvent(EntityHandle entity)
        : entity(entity)
    {
    }
};

} // namespace texplr
