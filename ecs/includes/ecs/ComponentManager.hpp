#pragma once

#include <map>
#include <memory>

#include <core/EventBus.hpp>
#include <core/EntityHandle.hpp>
#include <ecs/Events.hpp>

namespace texplr {

class BaseComponentManager { };

template <typename T>
class ComponentManager : public BaseComponentManager {
public:
    ComponentManager(std::shared_ptr<EventBus> eventBus)
        : m_eventBus(eventBus)
    {
        m_eventBus->subscribe(this, &ComponentManager::OnEntityDestroyed);
    }

    ~ComponentManager()
    {
        m_eventBus->unsubscribe<ComponentManager<T>, EntityDestroyedEvent>(this);
        m_components.clear();
    }

    void OnEntityDestroyed(EntityDestroyedEvent* event)
    {
        remove(event->entity);
    }

    T& get(EntityHandle entity)
    {
        return m_components.at(entity);
    }

    void add(EntityHandle entity, const T& component)
    {
        if (has(entity)) {
            remove(entity);
        }

        m_components[entity] = component;
        m_eventBus->notify(new ComponentAddedEvent<T>(entity, component));
    }

    void remove(EntityHandle entity)
    {
        if (has(entity)) {
            auto componentLoc = m_components.find(entity);
            T component = componentLoc->second;
            m_components.erase(componentLoc);
            m_eventBus->notify(new ComponentRemovedEvent<T>(entity, component));
        }
    }

    bool has(EntityHandle entity)
    {
        return m_components.find(entity) != m_components.end();
    }

private:
    std::shared_ptr<EventBus> m_eventBus;
    std::map<EntityHandle, T> m_components;
};

} // namespace texplr
