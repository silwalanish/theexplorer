#include <core/Scene.hpp>

#include <core/Application.hpp>

namespace texplr {

Scene::Scene(std::shared_ptr<EventBus> eventBus)
    : m_eventBus(eventBus)
{
}

Scene::~Scene()
{
}

void Scene::registerApplication(Application* application)
{
    m_application = application;
    m_inputManager = std::make_shared<Input>(application->getWindow());
}

void Scene::init()
{
    if (m_isInitialized) {
        return;
    }

    OnInit();
    m_isInitialized = true;
}

void Scene::update(float deltaTime)
{
    OnUpdate(deltaTime);

    m_inputManager->resetOffset();
}

std::shared_ptr<Input> Scene::getInputManager() const
{
    return m_inputManager;
}

std::shared_ptr<EventBus> Scene::getEventBus() const
{
    return m_eventBus;
}

std::shared_ptr<GameWindow> Scene::getWindow() const
{
    return m_application->getWindow();
}

} // namespace texplr
