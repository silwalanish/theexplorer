#include <ecs/World.hpp>

#include <core/Scene.hpp>
#include <ecs/systems/TransformSystem.hpp>

namespace texplr {

World::World(std::shared_ptr<EventBus> eventBus)
    : m_eventBus(eventBus)
{
    registerSystem<TransformSystem>();

    m_eventBus->subscribe(this, &World::OnEntityCreated);
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

void World::addChild(const EntityHandle& parent, const EntityHandle& child)
{
    m_scene->addChild(parent, child);
}

void World::removeChild(const EntityHandle& parent, const EntityHandle& child)
{
    m_scene->removeChild(parent, child);
}

const std::set<EntityHandle>& World::getChildren(const EntityHandle& parent) const
{
    return m_scene->getChildren(parent);
}

EntityHandle World::getParent(const EntityHandle& child) const
{
    return m_scene->getParent(child);
}

void World::registerToScene(Scene* scene)
{
    m_scene = scene;

    if (!hasComponent<Transform>(m_scene->getRoot())) {
        addComponent<Transform>(m_scene->getRoot(), Transform {});
    }
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
    return m_scene->getSceneGraph();
}

void World::OnEntityCreated(EntityCreatedEvent* event)
{
    addComponent<Transform>(event->entity, Transform {});
}

} // namespace texplr
