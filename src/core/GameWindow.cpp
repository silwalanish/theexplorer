#include <core/GameWindow.hpp>

#include <stdexcept>

namespace texplr {

GameWindow::GameWindow(const std::string& title, uint16_t width, uint16_t height)
    : m_title(title)
    , m_width(width)
    , m_height(height)
{
    m_handle = glfwCreateWindow(static_cast<int>(m_width), static_cast<int>(m_height), m_title.c_str(), nullptr, nullptr);

    if (!m_handle) {
        throw new std::runtime_error("Couldn't create a window!");
    }
}

GameWindow::~GameWindow()
{
}

void GameWindow::swapBuffers()
{
    glfwSwapBuffers(m_handle);
}

void GameWindow::destroy()
{
    if (m_handle) {
        glfwDestroyWindow(m_handle);
        m_handle = nullptr;
    }
}

bool GameWindow::shouldClose() const
{
    return glfwWindowShouldClose(m_handle);
}

} // namespace texplr
