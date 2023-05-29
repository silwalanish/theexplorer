#include <core/Application.hpp>

#include <GL/glew.h>
#include <iostream>

#include <components/Camera.hpp>
#include <components/Transform.hpp>
#include <ecs/Entity.hpp>
#include <systems/ActiveCameraFinder.hpp>

namespace texplr {

Application::Application()
    : m_glfwContext(4, 3)
    , m_window("The Explorer!", 800, 600)
    , m_glewContext(m_window)
{
    m_eventBus = std::make_shared<EventBus>();
    m_world = std::make_shared<World>(m_eventBus);
    m_world->registerSystem<ActiveCameraFinder>();

    Entity* camera = new Entity(m_world.get());
    camera->addComponent<Camera>(Camera { 0.01f, 100.0f, 45.0f, 1.33f, true });

    Entity* activeCamera = new Entity(m_world.get());
    activeCamera->addComponent<Camera>(Camera { 0.01f, 100.0f, 90.0f, 1.33f, true });
    activeCamera->addComponent<Transform>(Transform { 1.0f, 0.0f, 1.0f });

    std::cout << "Camera has both (Camera and Transform):: " << m_world->hasAllComponent<Transform, Camera>(camera->getHandle()) << std::endl;
    std::cout << "Active Camera has both (Camera and Transform):: " << m_world->hasAllComponent<Transform, Camera>(activeCamera->getHandle()) << std::endl;

    Entity* player = new Entity(m_world.get());
    Entity* enemy = new Entity(m_world.get());
}

Application::~Application()
{
}

void Application::run()
{
    while (!m_window.shouldClose()) {
        glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_world->update(1.0f); // TODO: Calculate deltaTime

        m_window.swapBuffers();

        m_glfwContext.pollEvents();
    }

    m_glewContext.destroy();
    m_window.destroy();
    m_glfwContext.destroy();
}

} // namespace texplr
