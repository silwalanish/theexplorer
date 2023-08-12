#include <core/Scene.hpp>

#include <core/Application.hpp>

namespace texplr {

Scene::Scene(std::shared_ptr<EventBus> eventBus)
    : m_eventBus(eventBus)
{
    m_entityManager = std::make_unique<EntityManager>(m_eventBus);
    m_sceneGraph = std::make_shared<SceneGraph>(createEntity());
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

EntityHandle Scene::createEntity()
{
    EntityHandle entity = m_entityManager->createEntity();

    if (m_sceneGraph) {
        m_sceneGraph->addChild(m_sceneGraph->getRoot(), entity);
    }

    return entity;
}

void Scene::destroyEntity(EntityHandle handle)
{
    m_sceneGraph->removeChild(m_sceneGraph->getParent(handle), handle);
    m_entityManager->destroyEntity(handle);
}

void Scene::addChild(const EntityHandle& parent, const EntityHandle& child)
{
    m_sceneGraph->addChild(parent, child);
}

void Scene::removeChild(const EntityHandle& parent, const EntityHandle& child)
{
    m_sceneGraph->removeChild(parent, child);
}

EntityHandle Scene::getRoot() const
{
    return m_sceneGraph->getRoot();
}

const std::set<EntityHandle>& Scene::getChildren(const EntityHandle& parent) const
{
    return m_sceneGraph->getChildren(parent);
}

EntityHandle Scene::getParent(const EntityHandle& child) const
{
    return m_sceneGraph->getParent(child);
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

std::shared_ptr<SceneGraph> Scene::getSceneGraph() const
{
    return m_sceneGraph;
}

} // namespace texplr
