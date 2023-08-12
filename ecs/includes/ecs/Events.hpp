#pragma once

#include <core/EntityHandle.hpp>
#include <core/Event.hpp>

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

} // namespace texplr
