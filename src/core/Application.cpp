#include <core/Application.hpp>

#include <GL/glew.h>

namespace texplr {

Application::Application()
    : m_glfwContext(4, 3)
    , m_window("The Explorer!", 800, 600)
    , m_glewContext(m_window)
{
}

Application::~Application()
{
}

void Application::run()
{
    while (!m_window.shouldClose()) {
        glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_window.swapBuffers();

        m_glfwContext.pollEvents();
    }

    m_glewContext.destroy();
    m_window.destroy();
    m_glfwContext.destroy();
}

} // namespace texplr
