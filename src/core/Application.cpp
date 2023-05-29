#include <core/Application.hpp>

#include <GL/glew.h>
#include <iostream>

#include <components/Camera.hpp>
#include <ecs/Entity.hpp>

namespace texplr {

Application::Application()
    : m_glfwContext(4, 3)
    , m_window("The Explorer!", 800, 600)
    , m_glewContext(m_window)
{
    m_world = std::make_shared<World>();

    Entity* camera = new Entity(m_world);
    camera->addComponent<Camera>(Camera { 0.01f, 100.0f, 90.0f, 1.33f, false });

    std::cout << "Camera ID:: " << camera->getHandle() << std::endl;
    std::cout << "Has Camera Component:: " << camera->hasComponent<Camera>() << std::endl;

    Camera& cam = camera->getComponent<Camera>();
    std::cout << "Camera:: " << cam.near << ", " << cam.far << ", " << cam.fov << ", " << cam.aspectRatio << ", " << cam.isActive << std::endl;
    cam.isActive = true;

    cam = camera->getComponent<Camera>();
    std::cout << "Updated Camera:: " << cam.near << ", " << cam.far << ", " << cam.fov << ", " << cam.aspectRatio << ", " << cam.isActive << std::endl;

    // TODO: Make sure components are removed when destroying entity
    camera->removeComponent<Camera>();
    std::cout << "Has Camera Component:: " << camera->hasComponent<Camera>() << std::endl;

    camera->destroy();
    delete camera;
    camera = nullptr;

    std::cout << "Camera destroyed!" << std::endl;

    Entity* player = new Entity(m_world);
    std::cout << "Player ID:: " << player->getHandle() << std::endl;
    std::cout << "Player Has Camera:: " << player->hasComponent<Camera>() << std::endl;

    Entity* enemy = new Entity(m_world);
    std::cout << "Enemy ID:: " << enemy->getHandle() << std::endl;
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
