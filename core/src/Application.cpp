#include <core/Application.hpp>

#include <GL/glew.h>
#include <chrono>

namespace texplr {

Application::Application()
    : m_glfwContext(4, 3)
    , m_eventBus(std::make_shared<EventBus>())
    , m_window(std::make_shared<GameWindow>(m_eventBus, "The Explorer!", 800, 600))
    , m_glewContext(*(m_window.get()))
{
    m_eventBus->subscribe(this, &Application::OnKeyDown);
    m_eventBus->subscribe(this, &Application::OnWindowClose);
}

Application::~Application()
{
}

void Application::run()
{
    m_running = true;

    std::chrono::steady_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    std::chrono::steady_clock::time_point currentTime;
    float deltaTime = 0.0f;

    while (m_running) {
        m_glfwContext.pollEvents();

        currentTime = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
        startTime = currentTime;

        if (m_scene) {
            m_scene->update(deltaTime);
        }

        m_window->swapBuffers();
    }

    m_glewContext.destroy();
    m_window->destroy();
    m_glfwContext.destroy();
}

void Application::stop()
{
    m_running = false;
}

std::shared_ptr<EventBus> Application::getEventBus() const
{
    return m_eventBus;
}

std::shared_ptr<Scene> Application::getScene() const
{
    return m_scene;
}

std::shared_ptr<GameWindow> Application::getWindow() const
{
    return m_window;
}

void Application::setScene(std::shared_ptr<Scene> scene)
{
    m_scene = scene;
    m_scene->registerApplication(this);
    m_scene->init();
}

void Application::OnKeyDown(KeyDownEvent* event)
{
    if (event->key == KeyCodes::ESCAPE) {
        m_running = false;
    }
}

void Application::OnWindowClose(WindowCloseEvent* event)
{
    if (event->window == m_window.get()) {
        m_running = false;
    }
}

} // namespace texplr
