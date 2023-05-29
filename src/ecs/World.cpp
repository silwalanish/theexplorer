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
}

} // namespace texplr
