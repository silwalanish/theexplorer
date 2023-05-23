#pragma once

#include <cstdint>
#include <string>

#include <GLFW/glfw3.h>

namespace texplr {

class GameWindow {
public:
    GameWindow(const std::string& title, uint16_t width, uint16_t height);
    ~GameWindow();

    void swapBuffers();
    void destroy();

    // TODO: Use events instead.
    bool shouldClose() const;

    operator GLFWwindow*() const
    {
        return m_handle;
    }

private:
    uint16_t m_width;
    uint16_t m_height;
    std::string m_title;

    GLFWwindow* m_handle = nullptr;
};

} // namespace texplr
