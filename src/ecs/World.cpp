#include <ecs/World.hpp>

namespace texplr {

World::World(std::shared_ptr<EventBus> eventBus)
    : m_eventBus(eventBus)
{
    m_entityManager = std::make_unique<EntityManager>(m_eventBus);
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
    return m_entityManager->createEntity();
}

void World::destroyEntity(EntityHandle handle)
{
    m_entityManager->destroyEntity(handle);
}

std::shared_ptr<EventBus> World::getEventBus() const
{
    return m_eventBus;
}

EntityHandle World::getActiveCamera() const
{
    return m_activeCamera;
}

void World::setActiveCamera(EntityHandle camera)
{
    m_activeCamera = camera;
}

} // namespace texplr
