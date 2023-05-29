#include <ecs/Entity.hpp>

namespace texplr {

Entity::Entity(std::shared_ptr<World> world)
    : m_handle(world->m_entityManager->createEntity())
    , m_world(world)
{
}

Entity::Entity(EntityHandle handle, std::shared_ptr<World> world)
    : m_handle(handle)
    , m_world(world)
{
}

Entity::Entity(const Entity& entity)
    : m_handle(entity.m_handle)
    , m_world(entity.m_world)
{
}

void Entity::destroy()
{
    m_world->m_entityManager->destroyEntity(m_handle);
    m_handle = 0;
}

EntityHandle Entity::getHandle() const
{
    return m_handle;
}

std::shared_ptr<World> Entity::getWorld() const
{
    return m_world;
}

bool Entity::isAlive() const
{
    return m_handle != 0;
}

} // namespace texplr
