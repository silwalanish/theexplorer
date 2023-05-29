#include <core/Application.hpp>

#include <GL/glew.h>

namespace texplr {

Application::Application()
    : m_glfwContext(4, 3)
    , m_window("The Explorer!", 800, 600)
    , m_glewContext(m_window)
{
    m_eventBus = std::make_shared<EventBus>();
}

Application::~Application()
{
}

void Application::run()
{
    while (!m_window.shouldClose()) {
        glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (m_scene) {
            m_scene->update(1.0f); // TODO: Calculate deltaTime
        }

        m_window.swapBuffers();

        m_glfwContext.pollEvents();
    }

    m_glewContext.destroy();
    m_window.destroy();
    m_glfwContext.destroy();
}

std::shared_ptr<EventBus> Application::getEventBus() const
{
    return m_eventBus;
}

std::shared_ptr<Scene> Application::getScene() const
{
    return m_scene;
}

void Application::setScene(std::shared_ptr<Scene> scene)
{
    m_scene = scene;
    m_scene->init();
}

} // namespace texplr
