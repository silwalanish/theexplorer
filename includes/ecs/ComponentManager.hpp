#pragma once

#include <map>
#include <memory>

#include <core/EventBus.hpp>
#include <ecs/EntityHandle.hpp>
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
        m_components[entity] = component;
    }

    void remove(EntityHandle entity)
    {
        if (has(entity)) {
            m_components.erase(m_components.find(entity));
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
