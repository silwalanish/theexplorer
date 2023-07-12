#include <ecs/Entity.hpp>

namespace texplr {

Entity::Entity(World* world)
    : m_handle(world->createEntity())
    , m_world(world)
{
}

Entity::Entity(EntityHandle handle, World* world)
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
    m_world->destroyEntity(m_handle);
    m_handle = 0;
}

void Entity::addScript(Script* script)
{
    m_world->addScript(m_handle, script);
}

World* Entity::getWorld()
{
    return m_world;
}

EntityHandle Entity::getHandle() const
{
    return m_handle;
}

const World* Entity::getWorld() const
{
    return m_world;
}

bool Entity::isAlive() const
{
    return m_handle != 0;
}

} // namespace texplr
