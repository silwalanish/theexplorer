#pragma once

#include <memory>

#include <ecs/EntityHandle.hpp>
#include <ecs/World.hpp>

namespace texplr {

struct Entity {
public:
    Entity(std::shared_ptr<World> world);
    Entity(EntityHandle handle, std::shared_ptr<World> world);
    Entity(const Entity& entity);

    template <typename ComponentType>
    void addComponent(const ComponentType& component)
    {
        m_world->getComponentManager<ComponentType>()->add(m_handle, component);
    }

    template <typename ComponentType>
    ComponentType& getComponent()
    {
        return m_world->getComponentManager<ComponentType>()->get(m_handle);
    }

    template <typename ComponentType>
    void removeComponent()
    {
        m_world->getComponentManager<ComponentType>()->remove(m_handle);
    }

    template <typename ComponentType>
    bool hasComponent()
    {
        return m_world->getComponentManager<ComponentType>()->has(m_handle);
    }

    void destroy();

    EntityHandle getHandle() const;
    std::shared_ptr<World> getWorld() const;
    bool isAlive() const;

private:
    EntityHandle m_handle = 0;
    std::shared_ptr<World> m_world = nullptr;
};

} // namespace texplr
