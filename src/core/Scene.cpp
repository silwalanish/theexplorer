#include <core/Application.hpp>
#include <core/Scene.hpp>

#include <components/Camera.hpp>
#include <components/DirectionalLight.hpp>

namespace texplr {

Scene::Scene(std::shared_ptr<EventBus> eventBus)
    : m_eventBus(eventBus)
{
    m_world = std::make_shared<World>(m_eventBus);
    m_world->registerToScene(this);
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
    m_world->update(deltaTime);
    OnUpdate(deltaTime);

    m_inputManager->resetOffset();
}

std::shared_ptr<Input> Scene::getInputManager() const
{
    return m_inputManager;
}

std::shared_ptr<World> Scene::getWorld() const
{
    return m_world;
}

std::shared_ptr<EventBus> Scene::getEventBus() const
{
    return m_eventBus;
}

std::shared_ptr<GameWindow> Scene::getWindow() const
{
    return m_application->getWindow();
}

EntityHandle Scene::getSun() const
{
    return m_sun;
}

EntityHandle Scene::getActiveCamera() const
{
    return m_activeCamera;
}

void Scene::setSun(EntityHandle sun)
{
    assert(m_world->hasComponent<DirectionalLight>(sun) && "Entity needs to have 'DirectionalLight' component.");

    m_sun = sun;
}

void Scene::setActiveCamera(EntityHandle camera)
{
    assert(m_world->hasComponent<Camera>(camera) && "Entity needs to have 'Camera' component.");

    m_activeCamera = camera;
}

} // namespace texplr
