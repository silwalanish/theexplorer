#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include <GLFW/glfw3.h>

#include <core/EventBus.hpp>

namespace texplr {

class GameWindow {
public:
    GameWindow(std::shared_ptr<EventBus> eventBus, const std::string& title, uint16_t width, uint16_t height);
    ~GameWindow();

    void swapBuffers();
    void destroy();

    void lockMouse();
    void unlockMouse();

    operator GLFWwindow*() const
    {
        return m_handle;
    }

    std::shared_ptr<EventBus> getEventBus() const;

private:
    uint16_t m_width;
    uint16_t m_height;
    std::string m_title;

    GLFWwindow* m_handle = nullptr;
    std::shared_ptr<EventBus> m_eventBus;
};

} // namespace texplr
