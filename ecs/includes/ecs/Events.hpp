#pragma once

#include <core/Event.hpp>
#include <core/EntityHandle.hpp>

namespace texplr {

template <typename ComponentType>
struct ComponentAddedEvent : public Event {
    const EntityHandle entity;
    const ComponentType& component;

    ComponentAddedEvent(EntityHandle entity, const ComponentType& component)
        : entity(entity)
        , component(component)
    {
    }
};

template <typename ComponentType>
struct ComponentRemovedEvent : public Event {
    const EntityHandle entity;
    const ComponentType& component;

    ComponentRemovedEvent(EntityHandle entity, const ComponentType& component)
        : entity(entity)
        , component(component)
    {
    }
};

struct EntityDestroyedEvent : public Event {
    const EntityHandle entity;

    EntityDestroyedEvent(EntityHandle entity)
        : entity(entity)
    {
    }
};

} // namespace texplr
