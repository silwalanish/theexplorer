#include <ecs/World.hpp>

#include <core/Scene.hpp>
#include <ecs/systems/TransformSystem.hpp>

namespace texplr {

World::World(std::shared_ptr<EventBus> eventBus)
    : m_eventBus(eventBus)
{
    m_entityManager = std::make_unique<EntityManager>(m_eventBus);

    registerSystem<TransformSystem>();

    m_sceneGraph = std::make_shared<SceneGraph>(createEntity());
    addComponent<Transform>(m_sceneGraph->getRoot(), Transform {});
}

World::~World()
{
}

void World::update(float deltaTime)
{
    for (auto& system : m_systems) {
        system->update(deltaTime);
    }
}

EntityHandle World::createEntity()
{
    EntityHandle entity = m_entityManager->createEntity();

    if (m_sceneGraph) {
        addComponent<Transform>(entity, Transform {});
        m_sceneGraph->addChild(m_sceneGraph->getRoot(), entity);
    }

    return entity;
}

void World::destroyEntity(EntityHandle handle)
{
    m_sceneGraph->removeChild(m_sceneGraph->getParent(handle), handle);
    m_entityManager->destroyEntity(handle);
}

void World::addChild(const EntityHandle& parent, const EntityHandle& child)
{
    m_sceneGraph->addChild(parent, child);
}

void World::removeChild(const EntityHandle& parent, const EntityHandle& child)
{
    m_sceneGraph->removeChild(parent, child);
}

const std::set<EntityHandle>& World::getChildren(const EntityHandle& parent) const
{
    return m_sceneGraph->getChildren(parent);
}

EntityHandle World::getParent(const EntityHandle& child) const
{
    return m_sceneGraph->getParent(child);
}

void World::registerToScene(Scene* scene)
{
    m_scene = scene;
}

Scene* World::getScene()
{
    return m_scene;
}

const Scene* World::getScene() const
{
    return m_scene;
}

std::shared_ptr<EventBus> World::getEventBus() const
{
    return m_eventBus;
}

std::shared_ptr<SceneGraph> World::getSceneGraph() const
{
    return m_sceneGraph;
}

} // namespace texplr
