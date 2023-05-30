#include <core/Application.hpp>

#include <GL/glew.h>
#include <chrono>

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
    std::chrono::steady_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    std::chrono::steady_clock::time_point currentTime;
    float deltaTime = 0.0f;

    while (!m_window.shouldClose()) {
        m_glfwContext.pollEvents();

        currentTime = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
        startTime = currentTime;

        glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (m_scene) {
            m_scene->update(deltaTime);
        }

        m_window.swapBuffers();
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
