#include <ecs/Entity.hpp>

namespace texplr {

Entity::Entity(World* world)
    : m_handle(world->getScene()->createEntity())
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

void Entity::addChild(const EntityHandle& child)
{
    m_world->addChild(m_handle, child);
}

void Entity::removeChild(const EntityHandle& child)
{
    m_world->removeChild(m_handle, child);
}

const std::set<EntityHandle>& Entity::getChildren() const
{
    return m_world->getChildren(m_handle);
}

EntityHandle Entity::getParent() const
{
    return m_world->getParent(m_handle);
}

void Entity::destroy()
{
    m_world->getScene()->destroyEntity(m_handle);
    m_handle = 0;
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
