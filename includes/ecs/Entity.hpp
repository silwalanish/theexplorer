#pragma once

#include <memory>

#include <ecs/EntityHandle.hpp>
#include <ecs/World.hpp>

namespace texplr {

struct Entity {
public:
    Entity(World* world);
    Entity(EntityHandle handle, World* world);
    Entity(const Entity& entity);

    template <typename ComponentType>
    void addComponent(const ComponentType& component)
    {
        m_world->addComponent(m_handle, component);
    }

    void addScript(Script* script);

    template <typename ComponentType>
    ComponentType& getComponent()
    {
        return m_world->getComponent<ComponentType>(m_handle);
    }

    template <typename ComponentType>
    void removeComponent()
    {
        m_world->removeComponent<ComponentType>(m_handle);
    }

    template <typename ComponentType>
    bool hasComponent()
    {
        return m_world->hasComponent<ComponentType>(m_handle);
    }

    void destroy();

    World* getWorld();

    EntityHandle getHandle() const;
    const World* getWorld() const;
    bool isAlive() const;

private:
    EntityHandle m_handle = 0;
    World* m_world = nullptr;
};

} // namespace texplr
